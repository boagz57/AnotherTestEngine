#include <array>
#include <cstdint>
#include "ErrorContext.h"

namespace Bgz
{
	namespace Err
	{
		thread_local std::array<const char*, 100> errorContextDescriptions{};
		thread_local std::array<const char*, 100> errorContextData{};
		thread_local uint16_t numContexts = 0;

		ErrContext::ErrContext(const char* c_ErrorContextDescription, const char* c_ErrorContexData /* default value = "" */)
		{
			errorContextDescriptions.at(numContexts) = c_ErrorContextDescription;
			errorContextData.at(numContexts) = c_ErrorContexData;
			++numContexts;
		}

		ErrContext::~ErrContext()
		{
			--numContexts;
		}

		auto ErrContext::LogContext() -> void
		{
			for (int i = 0; i < numContexts; ++i)
			{
				if (errorContextDescriptions.at(i) == nullptr)
					CONSOLE("ERROR with an error context description string being null!!!");
				if (errorContextData.at(i) == nullptr)
					CONSOLE("ERROR with error context data being null!!!");

				CONSOLE("  %s: %s\n", errorContextDescriptions.at(i), errorContextData.at(i));
			}
		}
	}
}