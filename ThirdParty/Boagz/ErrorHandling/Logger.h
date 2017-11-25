#pragma once
#include <cstdio>
#include <stdarg.h>

#if (BGZ_LOGGING_ON)
	#define CONSOLE(...) \
		do { fprintf_s(stderr, __VA_ARGS__); } while (0)

#else
	#define CONSOLE(...) __noop

#endif
