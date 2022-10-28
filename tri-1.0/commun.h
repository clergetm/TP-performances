#ifndef __COMMUN__
#define __COMMUN__

extern int quiet;
#define affiche(...) ((void) (quiet || printf(__VA_ARGS__)))

#ifdef __GNUC__
#define UNUSED(x) x __attribute__((unused))
#else 
#define UNUSED(x) x
#endif

#endif
