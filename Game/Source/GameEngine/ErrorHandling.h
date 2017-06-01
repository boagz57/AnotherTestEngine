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
				ErrorContext ec;
				for (int i = 0; i < ec.numContexts; ++i)
				{
					LOG("%s: %s\n", ec.errorContextDescriptions.at(i), ec.errorContextData.at(i));
					LOG("%s\n\n", message);
				}
				
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