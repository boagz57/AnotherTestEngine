#include <SDL.h>
#include "InputSystems.h"
#include "../../Components/Velocity.h"

namespace Blz
{
	namespace Input
	{
		namespace CompSystem
		{
			Comp::Velocity GatherDirectionalInput(Comp::Velocity fighterVelocity, Comp::Input input, Blz::Map<uint, bool>& keyMap)
			{
				if (input.IsFighterControllable())
				{
					if (keyMap[SDLK_w])
						fighterVelocity.Add(0.0f, 1.0f);
					else if (keyMap[SDLK_s])
						fighterVelocity.Add(0.0f, -1.0f);
					else if (keyMap[SDLK_a])
						fighterVelocity.Add(-1.0f, 0.0f);
					else if (keyMap[SDLK_d])
						fighterVelocity.Add(1.0f, 0.0f);
				}

				return fighterVelocity;
			}
		}
	}
}
