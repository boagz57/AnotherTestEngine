#include <stdarg.h>
#include <stdio.h>
#include "../Universal/Vector.h"
#include "ErrorContext.h"

namespace Blz
{
	namespace Err
	{
		Blz::Vector<const char*> ErrorContext::errorContextDescriptions;
		Blz::Vector<const char*> ErrorContext::errorContextData;
		uint16 ErrorContext::numContexts = 0;

		ErrorContext::ErrorContext(const char8* p_Description, const char8* p_Data)
		{
			errorContextDescriptions.reserve(40);
			errorContextData.reserve(40);

			errorContextDescriptions.push_back(p_Description);
			errorContextData.push_back(p_Data);
			++numContexts;
		}

		ErrorContext::ErrorContext()
		{}

		ErrorContext::~ErrorContext()
		{
			--numContexts;
		}
	}
}
