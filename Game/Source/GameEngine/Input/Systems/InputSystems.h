#pragma once
#include "Containers/Map.h"
#include "../../Components/Velocity.h"

namespace Blz
{
	namespace Input
	{
		namespace CompSystem
		{
			Comp::Velocity GatherDirectionalInput(Comp::Velocity velocity, Blz::Map<uint, bool>& keyMap);
		}
	}
}
