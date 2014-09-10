/* -*-c-*- */

#ifndef CMDPARSER_H
#define CMDPARSER_H

/* ---------------------------- included header files ---------------------- */

/* ---------------------------- global definitions ------------------------- */

/* ---------------------------- global macros ------------------------------ */

/* ---------------------------- type definitions --------------------------- */

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
	/* current function nesting depth */
	int call_depth;
} cmdparser_context_t;

typedef struct
{
	/* in general, functions in this structure that return int return
	 *    0: success
	 *  > 0: unsuccessful but not an error condition
	 *  < 0: unsuccessful, error
	 */
	int (*create_context)(
		cmdparser_context_t *dest_context,
		cmdparser_context_t *caller_context, char *line);
	int (*handle_line_start)(cmdparser_context_t *context);
	void (*destroy_context)(cmdparser_context_t *context);
} cmdparser_hooks_t;

#endif /* CMDPARSER_H */
