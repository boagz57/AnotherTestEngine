#include <SDL.h>
#include "InputSystems.h"
#include "../../Components/Velocity.h"

namespace Blz
{
	namespace Input
	{
		namespace System
		{
			VelocityComponent GatherDirectionalInput(VelocityComponent fighterVelocity, Blz::Map<uint, bool>& keyMap)
			{
				if (keyMap[SDLK_w])
					fighterVelocity.Add(0.0f, 1.0f);
				else if (keyMap[SDLK_s])
					fighterVelocity.Add(0.0f, -1.0f);
				else if (keyMap[SDLK_a])
					fighterVelocity.Add(-1.0f, 0.0f);
				else if (keyMap[SDLK_d])
					fighterVelocity.Add(1.0f, 0.0f);

				return fighterVelocity;
			}
		}
	}
}
