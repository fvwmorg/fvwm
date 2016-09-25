#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <bsd/stdio.h>
#include <bsd/sys/tree.h>

/* !BSD:   gcc -ggdb config.c -o config -lbsd */

struct args_comp {
	char		 	 key;
	char			*value;
	RB_ENTRY(args_comp)	 ent;
};
RB_HEAD(args_tree, args_comp);

struct arguments {
	struct args_tree	  tree;
	char			**argv;
	int			  argc;
};

struct cmd_ent {
	const char	*name;
	const char	*usage;
	const char	*getopt;
};

struct config_line {
	const char	*line;
	size_t		 line_no;
};

enum parsing_state {
	PARSING_LINE = 0,
	PARSING_HEREDOC,
	PARSING_HEREDOC_DONE
};

/* Forward declarations. */
static int	 args_cmp(struct args_comp *, struct args_comp *);
static void	 append_str(char **, char *, char *);

int args_cmp(struct args_comp *ac1, struct args_comp *ac2)
{
	return (ac1->key - ac2->key);
}

RB_GENERATE(args_tree, args_comp, ent, args_cmp);

void
append_str(char **append, char *src, char *delim)
{
	char	*result;

	if ((*append == NULL || *append[0] == '\0') || delim == NULL) {
		*append = strdup(src);
		return;
	}

	asprintf(&result, "%s%s%s", *append, delim, src);

	free(*append);
	*append = strdup(result);
	free(result);
}

int main(const char *argc, int argv)
{
	FILE			*f;
	size_t	 	 	 line = 0;
	char			*buf = NULL, *cp, *tmp, *cp_line = NULL;
	char			*cp_tmp, *full_hd = NULL;
	const char 		*config = "./config_file", *hd_end;
	enum parsing_state	 ps = PARSING_LINE;
	char			*config_lines[4096];
	size_t			 cl_count = 0;

	/* FIXME:  config_lines at 4096 maximum is bad! */
	memset(config_lines, '\0', sizeof config_lines);

	if ((f = fopen(config, "rb")) == NULL) {
		fprintf(stderr, "Couldn't open '%s': %s\n",
			config, strerror(errno));

		return (EXIT_FAILURE);
	}

	while ((buf = fparseln(f, NULL, &line, NULL, 0)) != NULL) {
		cp = buf;
		cp += strspn(cp, " \t\n");
		if (cp[0] == '\0') {
			free(buf);
			continue;
		}

		if (hd_end != NULL && (strcmp(cp, hd_end) == 0))
			ps = PARSING_HEREDOC_DONE;

		switch (ps) {
		case PARSING_LINE:
			if (strstr(cp, "<<") != NULL)
				break;
			append_str(&config_lines[line], cp, NULL);
			break;
		case PARSING_HEREDOC:
			append_str(&cp_line, cp, ",");
			break;
		case PARSING_HEREDOC_DONE:
			append_str(&full_hd, cp_line, " ");
			append_str(&config_lines[line], full_hd, NULL);

			free(buf);
			free((char *)hd_end);
			free(cp_line);
			free(full_hd);
			break;
		default:
			break;
		}

		char *cp_tmp = strdup(cp);
		if ((tmp = strtok(cp_tmp, "<<")) != NULL) {
			if ((cp = strstr(cp, "<<")) != NULL) {
				cp += 2;
				ps = PARSING_HEREDOC;

				append_str(&full_hd, tmp, NULL);
				hd_end = strdup(cp);
			}
		}
		free(cp_tmp);
	}

	for (cl_count = 0; cl_count < line; cl_count++) {
		if (config_lines[cl_count] == NULL) {
			continue;
		}
		printf("[%d]: %s\n", cl_count, config_lines[cl_count]);
	}

	return (EXIT_SUCCESS);
}
