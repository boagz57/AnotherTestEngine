#pragma once
#include <cstdio>
#include <assert.h>
#include "Boost/BoostAssert.h"

#define RUNTIME_ASSERT \
	BOOST_ASSERT_MSG 

#define COMPILETIME_ASSERT(expr, msg) \
	static_assert(expr, msg) 

#if (_DEBUG)
#define LOG(...) \
	do { fprintf(stderr, __VA_ARGS__); } while (0)

#else
#define NDEBUG
#define LOG(...) 
#endif

