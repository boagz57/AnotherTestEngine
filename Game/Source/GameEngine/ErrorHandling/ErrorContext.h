#pragma once
#include "Containers/SmallVector.h"

namespace Blz
{
	namespace Err
	{
		class ErrContext
		{
		public:
			ErrContext();
			~ErrContext();
			ErrContext(const ErrContext& copy) = delete;
			void operator=(const ErrContext& copy) = delete;

			void AddContext(const char* errorContextDescription, const char* errorContexData = "");
			static void LogContext();

		private:
			static Blz::SmallVector<const char*> errorContextDescriptions;
			static Blz::SmallVector<const char*> errorContextData;
			static uint16 numContexts;
		};
	};
}
