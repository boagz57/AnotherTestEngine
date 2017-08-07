#pragma once
#include "../../Fighter.h"
#include "../../../Universal/SmallVector.h"

namespace Blz
{
	namespace Physics
	{
		Blz::SmallVector<Fighter> AABBCollisionSystem(Blz::SmallVector<Fighter> fighters);
	}
}
