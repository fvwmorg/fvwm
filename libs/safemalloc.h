/* -*-c-*- */

/*
 *
 *  Procedure:
 *      safe?alloc - mallocs/callocs specified space or exits if there's a
 *                   problem
 *
 */
void *safemalloc(size_t);
void *safecalloc(size_t, size_t);
void *saferealloc(void *, size_t);
char *safestrdup(const char *s);
