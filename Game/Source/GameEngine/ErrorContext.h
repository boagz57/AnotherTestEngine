#pragma once
#include "../Universal/Vector.h"

namespace Blz
{
	namespace Err
	{
		class ErrorContext
		{
		public:
			ErrorContext(const char8* errorContextDescription, const char8* errorContextData);
			~ErrorContext();
			ErrorContext(const ErrorContext& copy) = delete;
			void operator=(const ErrorContext& copy) = delete;

		private:
			friend void ErrReport(bool, const char*);
			ErrorContext();
			static Blz::Vector<const char8*> errorContextDescriptions;
			static Blz::Vector<const char8*> errorContextData;
			static uint16 numContexts;
		};
	};
}

