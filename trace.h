#ifndef TRACE_H
#define TRACE_H

#include "git-compat-util.h"
#include "strbuf.h"

extern void trace_repo_setup(const char *prefix);
extern int trace_want(const char *key);
extern uint64_t getnanotime(void);

#ifndef HAVE_VARIADIC_MACROS

__attribute__((format (printf, 1, 2)))
extern void trace_printf(const char *format, ...);

__attribute__((format (printf, 2, 3)))
extern void trace_printf_key(const char *key, const char *format, ...);

__attribute__((format (printf, 2, 3)))
extern void trace_argv_printf(const char **argv, const char *format, ...);

extern void trace_strbuf(const char *key, const struct strbuf *data);

#else

/*
 * Macros to add file:line - see above for C-style declarations of how these
 * should be used.
 */

/*
 * Note: with C99 variadic macros, __VA_ARGS__ must include the last fixed
 * parameter ('format' in this case). Otherwise, a call without variable
 * arguments will have a surplus ','. E.g.:
 *
 *  #define foo(format, ...) bar(format, __VA_ARGS__)
 *  foo("test");
 *
 * will expand to
 *
 *  bar("test",);
 *
 * which is invalid (note the ',)'). With GNUC, '##__VA_ARGS__' drops the
 * comma, but this is non-standard.
 */

#define trace_printf(...) \
	trace_printf_key_fl(__FILE__, __LINE__, "GIT_TRACE", __VA_ARGS__)

#define trace_printf_key(key, ...) \
	trace_printf_key_fl(__FILE__, __LINE__, key, __VA_ARGS__)

#define trace_argv_printf(argv, ...) \
	trace_argv_printf_fl(__FILE__, __LINE__, argv, __VA_ARGS__)

#define trace_strbuf(key, data) \
	trace_strbuf_fl(__FILE__, __LINE__, key, data)

/* backend functions, use non-*fl macros instead */
__attribute__((format (printf, 4, 5)))
extern void trace_printf_key_fl(const char *file, int line, const char *key,
				const char *format, ...);
__attribute__((format (printf, 4, 5)))
extern void trace_argv_printf_fl(const char *file, int line, const char **argv,
				 const char *format, ...);
extern void trace_strbuf_fl(const char *file, int line, const char *key,
			    const struct strbuf *data);

#endif /* HAVE_VARIADIC_MACROS */

#endif /* TRACE_H */
