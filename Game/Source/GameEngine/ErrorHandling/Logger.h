#pragma once

#if (DEBUG)
	#define LOG(...) \
		do { fprintf_s(stderr, __VA_ARGS__); } while (0)

#else
	#define LOG(...) ((void)0)

#endif
