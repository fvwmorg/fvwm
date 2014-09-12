/* -*-c-*- */

#ifndef CMDPARSER_HOOKS_H
#define CMDPARSER_HOOKS_H

/* ---------------------------- included header files ---------------------- */

/* ---------------------------- global definitions ------------------------- */

/* ---------------------------- global macros ------------------------------ */

/* ---------------------------- type definitions --------------------------- */

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
	/* expandeds the command line */
	void (*expand_command_line)(
		cmdparser_context_t *context, int is_addto, void *func_rc,
		const void *exc);
	/* Release the expline field from the context structure and return it.
	 * It is then the responsibility of the caller to free() it. */
	void (*release_expanded_line)(cmdparser_context_t *context);
	/* Tries to find a builtin function, a complex function or a module
	 * config line to execute and returns the type found or
	 * CP_EXECTYPE_UNKNOWN if none of the above was identified.  For a
	 * builtin or a complex funtion the pointer to the description is
	 * returned in *ret_builtin or *ret_complex_function.  Consumes the
	 * the "Module" or the "Function" command form the input.  Dos not
	 * consider builtin functions if *ret_builtin is != NULL when the
	 * function is called.  */
	cmdparser_execute_type_t (*find_something_to_execute)(
		cmdparser_context_t *context,
		const func_t **ret_builtin,
		FvwmFunction **ret_complex_function);
	/* Release the context initialised with create_context(). */
	void (*destroy_context)(cmdparser_context_t *context);
	/* Print the contents of the context. */
	void (*debug)(cmdparser_context_t *context, const char *msg);
} cmdparser_hooks_t;

#endif /* CMDPARSER_HOOKS_H */
