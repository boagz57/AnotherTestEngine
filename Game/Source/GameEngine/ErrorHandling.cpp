#include <stdarg.h>
#include <stdio.h>
#include "ErrorHandling.h"

namespace Blz
{
	namespace Error
	{
		Blz::Vector<const char*> ErrorContext::errorContextDescriptions;
		Blz::Vector<const char*> ErrorContext::errorContextData;

		ErrorContext::ErrorContext()
		{}

		ErrorContext::ErrorContext(const char8* p_Description, const char8* p_Data) 
		{
			errorContextDescriptions.reserve(40);
			errorContextData.reserve(40);

			errorContextDescriptions.push_back(p_Description);
			errorContextData.push_back(p_Data);
		}

		ErrorContext::ErrorContext(const char8 * errorContextDescription)
		{
			errorContextDescriptions.reserve(40);
			errorContextData.reserve(40);
		}

		ErrorContext::~ErrorContext()
		{
			errorContextDescriptions.pop_back();
			errorContextData.pop_back();
		}

		void ErrorContext::AddContextInfo(const char * errorContextDescription)
		{
			errorContextDescriptions.push_back(errorContextDescription);
		}

		void ErrorContext::AddContextInfo(const char * errorContextDescription, const char * errorContextData)
		{
			errorContextDescriptions.push_back(errorContextDescription);
			errorContextDescriptions.push_back(errorContextData);
		}
	}
}
