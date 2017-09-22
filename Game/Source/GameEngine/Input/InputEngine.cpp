#include <SDL.h>
#include "../Fighter.h"
#include "InputEngine.h"

namespace Blz
{
	namespace Input
	{
		auto Engine::Update(Scene& scene) -> void
		{
			ec.AddContext("When updating input engine");

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
				{//Take action on input
					if (fighter.GetInput().IsFighterControllable())
					{
						if (this->keyMap[SDLK_d])
							fighter.GetInput().KeyPressed(SDLK_d, &fighter);
						if (this->keyMap[SDLK_a])
							fighter.GetInput().KeyPressed(SDLK_a, &fighter);
						if (this->keyMap[SDLK_w])
							fighter.GetInput().KeyPressed(SDLK_w, &fighter);
						if (this->keyMap[SDLK_s])
							fighter.GetInput().KeyPressed(SDLK_s, &fighter);
					}
				}
			}
		}
	}
}