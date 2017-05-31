#pragma once
#include <cstdio>
#include "ErrorContext.h"

namespace Blz
{
	namespace Error
	{
		inline void Log(bool IsValidVar, const char* message, ErrorContext &ec)
		{
			if (!IsValidVar)
			{
			}
		}

		template<typename T> inline bool Check(T* ptr)
		{
			if (ptr == nullptr)
				return false;

			return true;
		}

		template<typename T> inline bool Check(T)
		{

		}
	}
}