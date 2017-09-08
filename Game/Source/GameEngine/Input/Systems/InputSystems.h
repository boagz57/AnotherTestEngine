#pragma once
#include "Containers/Map.h"
#include "../../Components/Velocity.h"
#include "../../Components/Input.h"

namespace Blz
{
	namespace Input
	{
		namespace CompSystem
		{
			Comp::Velocity GatherDirectionalInput(Comp::Velocity velocity, Comp::Input input, Blz::Map<uint, bool>& keyMap);
		}
	}
}
