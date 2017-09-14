#pragma once
#include "Containers/SmallVector.h"
#include "ErrorContext.h"

namespace Blz
{
	namespace Err
	{
		Blz::SmallVector<Blz::string> ErrContext::errorContextDescriptions;
		Blz::SmallVector<Blz::string> ErrContext::errorContextData;
		uint16 ErrContext::numContexts = 0;

		ErrContext::ErrContext()
		{
			errorContextDescriptions.reserve(40);
			errorContextData.reserve(40);
		}

		ErrContext::~ErrContext()
		{
			errorContextDescriptions.pop_back();
			errorContextData.pop_back();
			--numContexts;
		}

		void ErrContext::AddContext(const Blz::string c_ErrorContextDescription, const Blz::string c_ErrorContexData /* default value = "" */)
		{
			#if (DEBUG)
				errorContextDescriptions.push_back(c_ErrorContextDescription);
				errorContextData.push_back(c_ErrorContexData);
				++numContexts;

			#elif (PROFILE)

			#endif
		}

		void ErrContext::LogContext()
		{
			for (int i = 0; i < numContexts; ++i)
			{
				LOG("  %s: %s\n", errorContextDescriptions.at(i).c_str(), errorContextData.at(i).c_str());
			}
		}
	}
}

Blz::Err::ErrContext ec;