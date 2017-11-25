#include <array>
#include "Logger.h"
#include "ErrorContext.h"

namespace Bgz
{
	namespace Err
	{
		thread_local std::array<const char*, 100> errorContextDescriptions{};
		thread_local std::array<const char*, 100> errorContextData{};
		thread_local unsigned int numContexts = 0;

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
			for (unsigned int i = 0; i < numContexts; ++i)
			{
				if (errorContextDescriptions.at(i) == nullptr)
					fprintf_s(stderr, "ERROR with an error context description string being null!!!");
				if (errorContextData.at(i) == nullptr)
					fprintf_s(stderr, "ERROR with error context data being null!!!");

				fprintf_s(stderr, "  %s: %s\n", errorContextDescriptions.at(i), errorContextData.at(i));
			}
		}
	}
}