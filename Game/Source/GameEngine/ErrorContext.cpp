#include "../Universal/Vector.h"
#include "ErrorContext.h"

namespace Blz
{
	namespace Err
	{
		Blz::Vector<Blz::string> ErrorContext::errorContextDescriptions;
		Blz::Vector<Blz::string> ErrorContext::errorContextData;
		uint16 ErrorContext::numContexts = 0;

		ErrorContext::ErrorContext(const Blz::string p_Description, const Blz::string p_Data /* default value = "" */)
		{
			errorContextDescriptions.reserve(40);
			errorContextData.reserve(40);

			errorContextDescriptions.push_back(p_Description);
			errorContextData.push_back(p_Data);
			++numContexts;
		}

		ErrorContext::~ErrorContext()
		{
			errorContextDescriptions.pop_back();
			errorContextData.pop_back();
			--numContexts;
		}

		void ErrorContext::LogContext()
		{
			for (int i = 0; i < numContexts; ++i)
			{
				LOG("  %s: %s\n", errorContextDescriptions.at(i).c_str(), errorContextData.at(i).c_str());
			}
		}
	}
}
