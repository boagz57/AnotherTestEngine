#pragma once
#include "Containers\SmallVector.h"

namespace Blz
{
	namespace Err
	{
		class ErrContext
		{
		public:
			ErrContext(const char* c_ErrorContextDescription, const char* c_ErrorContexData = "");
			~ErrContext();
			ErrContext(const ErrContext& copy) = delete;
			void operator=(const ErrContext& copy) = delete;

			static auto LogContext() -> void;
		};
	};
}