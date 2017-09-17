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
			auto BindAxis(const int32 key, Fighter* const fighter, std::function<void(Fighter*)> movementFunction) -> void;
		};
	}
}

