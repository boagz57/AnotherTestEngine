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

			auto AddContext(const char* errorContextDescription, const char* errorContexData = "") -> void;
			static auto LogContext() -> void;

		private:
			static Blz::SmallVector<const char*> errorContextDescriptions;
			static Blz::SmallVector<const char*> errorContextData;
			static uint16 numContexts;
		};
	};
}
