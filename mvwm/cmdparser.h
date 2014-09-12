/* -*-c-*- */

#ifndef CMDPARSER_H
#define CMDPARSER_H

/* ---------------------------- included header files ---------------------- */

/* ---------------------------- global definitions ------------------------- */

#define CMDPARSER_NUM_POS_ARGS 10

/* ---------------------------- global macros ------------------------------ */

/* ---------------------------- type definitions --------------------------- */

typedef enum
{
	CP_PREFIX_NONE = 0,
	CP_PREFIX_MINUS = 0x1,
	CP_PREFIX_SILENT = 0x2,
	CP_PREFIX_KEEPRC = 0x4
} cmdparser_prefix_flags_t;

/* move this to the implementation file and use void* instead??? */

typedef struct
{
	/* !!!note: need to define which bits in here may be accessed by the
	 * user and which are internal */
	char is_created : 1;
	/* the original command line */
	char *line;
	/* the current command line */
	char *cline;
	/* the expanded command line */
	char *expline;
	int do_free_expline : 1;
	/* the command name */
	char *command;
	/* current function nesting depth */
	int call_depth;
	/* an array of positional arguments; the first array element contains
	 * a string with all positional arguments, the remaining ten array
	 * elements contain the first ten positional arguments.  Any of this
	 * may be NULL pointers */
	char *pos_args[CMDPARSER_NUM_POS_ARGS];
} cmdparser_context_t;

typedef struct
{
	/* in general, functions in this structure that return int return
	 *    0: success
	 *  > 0: unsuccessful but not an error condition
	 *  < 0: unsuccessful, error
	 */
	int (*create_context)(
		/* context structure to initialise */
		cmdparser_context_t *dest_context,
		/* context structure of the caller or NULL */
		cmdparser_context_t *caller_context,
		/* input command line */
		char *line,
		/* an array of positional arguments or NULL; the first array
		 * element contains a string with all positional arguments,
		 * the remaining ten array elements contain the first ten
		 * positional arguments, up to the first NULL pointer; may be
		 * NULL if not present */
		char *pos_args[]
		);
	int (*handle_line_start)(cmdparser_context_t *context);
	/* Returns a set of or'ed flags of which prefixes are present on the
	 * command line.  The prefixes are stripped.  */
	cmdparser_prefix_flags_t (*handle_line_prefix)(
		cmdparser_context_t *context);
	/* parses and returns the command name or returns a NULL pointer if not
	 * possible */
	const char *(*parse_command_name)(
		cmdparser_context_t *context, void *func_rc, const void *exc);
	/* returns 1 if the stored command is a module configuration command
	 * and 0 otherwise */
	int (*is_module_config)(cmdparser_context_t *context);
	/* returns the expanded command line */
	char *(*expand_command_line)(
		cmdparser_context_t *context, int is_addto, void *func_rc,
		const void *exc);
	/* Release the expline field from the context structure and return it.
	 * It is then the responsibility of the caller to free() it. */
	void (*release_expanded_line)(cmdparser_context_t *context);
	void (*destroy_context)(cmdparser_context_t *context);
	void (*debug)(cmdparser_context_t *context, const char *msg);
} cmdparser_hooks_t;

#endif /* CMDPARSER_H */
