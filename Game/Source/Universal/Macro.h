#pragma once
#include <cstdio>
#include <stdarg.h>
#include <assert.h>
#include <Boost/BoostAssert.h>

inline void ErrorLog(int lineNumberOfError, const char* fileOfError, const char* msg, ...)
{
	//Captures ellipses arguments
	va_list argptr;
	va_start(argptr, msg);//Initializes the va_list

	fprintf(stderr, "In %s\n Line: %i\n", fileOfError, lineNumberOfError);
	fprintf(stderr, msg);

	//cleans up argptr va_list
	va_end(argptr);
}

#if (_DEBUG)

#define RUNTIME_ASSERT \
	BOOST_ASSERT_MSG 

#define COMPILETIME_ASSERT(expr, msg) \
	static_assert(expr, msg) 

#define LOG(...) \
	do { fprintf(stderr, __VA_ARGS__); } while (0)

#define XASSERT(test, msg, ...) \
	do {if (test) ErrorLog(__LINE__, __FILE__, msg, __VA_ARGS__);} while (0)

#else
#define NDEBUG
#define RUNTIME_ASSERT
#define COMPILETIME_ASSERT(expr, msg) 
#define LOG(...) ((void)0)
#define XASSERT(test, msg, ...) ((void)0)
#endif

