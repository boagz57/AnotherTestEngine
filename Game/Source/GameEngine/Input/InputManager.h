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
			auto BindAxis(int32 key, Fighter* fighter, std::function<void(Fighter*)> movementFunction) -> void;
		};
	}
}

