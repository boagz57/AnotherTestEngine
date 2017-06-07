#pragma once
#include <cstdio>
#include <stdarg.h>
#include <assert.h>
#include <Boost/BoostAssert.h>

#if (_DEBUG) || (PROFILE)

#define RUNTIME_ASSERT \
	BOOST_ASSERT_MSG 

#define COMPILETIME_ASSERT(expr, msg) \
	static_assert(expr, msg) 

#define LOG(...) \
	do { fprintf_s(stderr, __VA_ARGS__); } while (0)

#else
#define NDEBUG
#define RUNTIME_ASSERT
#define COMPILETIME_ASSERT(expr, msg) 
#define LOG(...) ((void)0)
#endif

