/* -*-c-*- */

/*
 *
 *  Procedure:
 *      safe?alloc - mallocs/callocs specified space or exits if there's a
 *                   problem
 *
 */

#ifndef HAVE_ASPRINTF
int		 asprintf(char **, const char *, ...);
int		 vasprintf(char **, const char *, va_list);
#endif

void *safemalloc(size_t);
void *safecalloc(size_t, size_t);
void *saferealloc(void *, size_t);
char *safestrdup(const char *s);
