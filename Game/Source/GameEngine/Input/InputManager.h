#pragma once
#include <functional>
#include "Fighter.h"

namespace Blz
{
	namespace Input
	{
		class Manager
		{
		public:
			void BindAxis(int32 key, Fighter* fighter, std::function<void(Fighter*)> movementFunction);
		};
	}
}

