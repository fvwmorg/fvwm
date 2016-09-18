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

/* Forward declarations. */
int	 args_comp(struct args_comp *, struct args_comp *);

int args_cmp(struct args_comp *ac1, struct args_comp *ac2)
{
	return (ac1->key - ac2->key);
}

RB_GENERATE(args_tree, args_comp, ent, args_cmp);

int main(const char *argc, int argv)
{
	FILE		*f;
	size_t	 	 line;
	char		*buf = NULL, *cp;
	const char 	*config = "./config_file";

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

		printf("%s [%d]: <<%s>>\n", config, line, buf);
	}

	return (EXIT_SUCCESS);
}
