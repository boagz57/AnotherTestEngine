#pragma once
#include <cstdio>
#include <stdarg.h>

#if (DEBUG) || (PROFILE)

#define LOG(...) \
	do { fprintf_s(stderr, __VA_ARGS__); } while (0)

//Used so I can have a build configuration setup with the same settings as the default debug configuration but with LOG
//messages turned off. Helps unclutter unit tests as before LOG messages would be scattered about unit tests in console
#elif (DEBUGUNIT) || (PROFILEUNIT)

#define LOG(...) ((void)0)

#else

#define NDEBUG
#define LOG(...) ((void)0)

#endif
