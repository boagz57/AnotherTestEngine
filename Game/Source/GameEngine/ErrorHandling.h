#pragma once
#include <cstdio>
#include "ErrorContext.h"

namespace Blz
{
	namespace Err
	{
		inline void ErrReport(const char8* fileOfError, int32 lineNumberOfError, const Blz::string c_errMessage)
		{
			ErrorContext::LogContext();
			LOG("  ERROR: %s\n", c_errMessage.c_str());
			LOG("  In %s: %i\n\n", fileOfError, lineNumberOfError);
			exit(0);
		}

		#if(_DEBUG)
			#define ERRASSERT(test, msg) do {if (!(test)) Blz::Err::ErrReport(__FILE__, __LINE__, msg);} while (0)
		#endif
	}
}