#pragma once
#include <string>
#include <stdint.h>

typedef unsigned int uint;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef size_t sizeofobject;
typedef char char8; //TODO: Replace all char8 in code with regular char and then delete this. I don't this char is much of a problem on different platforms
typedef unsigned char uchar8; //Same thing here as above
typedef float sfloat;
typedef double dfloat;
namespace Blz { typedef std::string string; }; //TODO: Replace with EASTL string class