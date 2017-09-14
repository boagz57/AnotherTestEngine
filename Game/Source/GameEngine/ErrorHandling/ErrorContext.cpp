#pragma once
#include "Containers/SmallVector.h"
#include "ErrorContext.h"

namespace Blz
{
	namespace Err
	{
		Blz::SmallVector<const char*> ErrContext::errorContextDescriptions;
		Blz::SmallVector<const char*> ErrContext::errorContextData;
		uint16 ErrContext::numContexts = 0;

		ErrContext::ErrContext()
		{
			errorContextDescriptions.reserve(100);
			errorContextData.reserve(100);
		}

		ErrContext::~ErrContext()
		{
			errorContextDescriptions.pop_back();
			errorContextData.pop_back();
			--numContexts;
		}

		void ErrContext::AddContext(const char* c_ErrorContextDescription, const char* c_ErrorContexData /* default value = "" */)
		{
			#if (DEBUG)
				errorContextDescriptions.push_back(c_ErrorContextDescription);
				errorContextData.push_back(c_ErrorContexData);
				++numContexts;
			#endif
		}

		void ErrContext::LogContext()
		{
			for (int i = 0; i < numContexts; ++i)
			{
				LOG("  %s: %s\n", errorContextDescriptions.at(i), errorContextData.at(i));
			}
		}
	}
}

Blz::Err::ErrContext ec;