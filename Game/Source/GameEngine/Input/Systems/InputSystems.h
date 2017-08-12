#pragma once
#include "../../../Universal/Map.h"
#include "../../Components/Velocity.h"

namespace Blz
{
	namespace Input
	{
		namespace System
		{
			VelocityComponent GatherDirectionalInput(VelocityComponent velocity, Blz::Map<uint, bool>& keyMap);
		}
	}
}
