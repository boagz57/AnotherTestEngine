#pragma once
#include <cstdio>
#include "ErrorContext.h"

namespace Blz
{
	namespace Err
	{
		inline void ErrReport(bool IsValidVar, const char* message)
		{
			if (!IsValidVar)
			{
				ErrorContext::LogContext();
				LOG("ERROR: %s\n\n", message);
				exit(0);
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