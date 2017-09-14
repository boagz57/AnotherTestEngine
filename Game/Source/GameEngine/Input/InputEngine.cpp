#include <SDL.h>
#include "../Fighter.h"
#include "InputEngine.h"

namespace Blz
{
	namespace Input
	{
		void Engine::Update(Scene& scene)
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

				default:
					break;
				}
			}

			for (Fighter& fighter : scene.fighters)
			{
				if (fighter.input.IsFighterControllable())
				{
					if (keyMap[SDLK_d])
						fighter.input.KeyPressed(SDLK_d, &fighter);
					if (keyMap[SDLK_a])
						fighter.input.KeyPressed(SDLK_a, &fighter);
					if (keyMap[SDLK_w])
						fighter.input.KeyPressed(SDLK_w, &fighter);
					if (keyMap[SDLK_s])
						fighter.input.KeyPressed(SDLK_s, &fighter);
				}
			}
		}
	}
}