#pragma once
#include "Fighter.h"

namespace Blz
{
	namespace Input 
	{
		class GameLogic
		{
		public:
			static auto Bind(const int32 key, Fighter* const fighter, std::function<void(Fighter*)> movementFunction) -> void;
		};
	}
}

using BlzInput = Blz::Input::GameLogic;