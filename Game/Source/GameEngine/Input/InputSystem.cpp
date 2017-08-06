#include <SDL.h>
#include "../../Universal/UnorderedMap.h"
#include "../Fighter.h"
#include "InputSystem.h"

namespace Blz
{
	void InputSystem::ProcessInput(Scene& scene)
	{
		for (Fighter& fighter : scene.fighters)
		{
			while (SDL_PollEvent(&evnt))
			{
				switch (evnt.type)
				{
				case SDL_KEYDOWN:
					keyMap[evnt.key.keysym.sym] = true;
					break;

				case SDL_KEYUP:
					keyMap[evnt.key.keysym.sym] = false;
					break;
				}
			}

			if (fighter.IsFighterControllable())
			{
				if (keyMap[SDLK_w])
					fighter.velocity.Add(0.0f, 1.0f);
				else if (keyMap[SDLK_s])
					fighter.velocity.Add(0.0f, -1.0f);
				else if (keyMap[SDLK_a])
					fighter.velocity.Add(-1.0f, 0.0f);
				else if (keyMap[SDLK_d])
					fighter.velocity.Add(1.0f, 0.0f);
			};
		}
	}
}