#pragma once
#include "../Universal/Vector.h"

namespace Blz
{
	namespace Error
	{
		class ErrorContext
		{
		public:
			ErrorContext();
			ErrorContext(const char8* errorContextDescription, const char8* errorContextData);
			ErrorContext(const char8* errorContextDescription);
			~ErrorContext();
			ErrorContext(const ErrorContext& copy) = delete;
			void operator=(const ErrorContext& copy) = delete;

			void AddContextInfo(const char* errorContextDescription);
			void AddContextInfo(const char* errorContextDescription, const char* errorContextData);

		private:
			static Blz::Vector<const char8*> errorContextDescriptions;
			static Blz::Vector<const char8*> errorContextData;
		};
	};
}

