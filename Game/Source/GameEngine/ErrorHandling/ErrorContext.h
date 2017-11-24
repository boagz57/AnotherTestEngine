#pragma once

namespace Bgz
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
