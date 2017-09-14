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

			void AddContext(const Blz::string errorContextDescription, const Blz::string errorContexData = "");
			static void LogContext();

		private:
			static Blz::SmallVector<Blz::string> errorContextDescriptions;
			static Blz::SmallVector<Blz::string> errorContextData;
			static uint16 numContexts;
		};
	};
}
