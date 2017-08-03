#include <SDL.h>
#include "../Universal/UnorderedMap.h"
#include "Fighter.h"
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
					fighter.AddToPosition(0, 1, 0);
				else if (keyMap[SDLK_s])
					fighter.AddToPosition(0, -1, 0);
				else if (keyMap[SDLK_a])
					fighter.AddToPosition(-1, 0, 0);
				else if (keyMap[SDLK_d])
					fighter.AddToPosition(1, 0, 0);
			};
		}
	}
}