#pragma once
#include "../Universal/SmallVector.h"

namespace Blz
{
	namespace Err
	{
		class ErrorContext
		{
		public:
			ErrorContext(const Blz::string errorContextDescription, const Blz::string errorContextData = "");
			~ErrorContext();
			ErrorContext(const ErrorContext& copy) = delete;
			void operator=(const ErrorContext& copy) = delete;

			static void LogContext();

		private:
			static Blz::SmallVector<Blz::string> errorContextDescriptions;
			static Blz::SmallVector<Blz::string> errorContextData;
			static uint16 numContexts;
		};
	};
}

