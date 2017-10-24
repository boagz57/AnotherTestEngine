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

			for (Fighter* fighter : scene.fighters)
			{
				if (fighter->input.IsControllable())
				{
					while (SDL_PollEvent(&evnt))
					{
						switch (evnt.type)
						{
						case SDL_KEYDOWN:
							fighter->input.keyMap[evnt.key.keysym.sym] = true;
							break;

						case SDL_KEYUP:
							fighter->input.keyMap[evnt.key.keysym.sym] = false;
							break;

						default:
							break;
						}
					}

					if (fighter->input.keyMap[SDLK_d])
						fighter->input.KeyPressed(SDLK_d, fighter);
					if (fighter->input.keyMap[SDLK_a])
						fighter->input.KeyPressed(SDLK_a, fighter);
					if (fighter->input.keyMap[SDLK_SPACE])
						fighter->input.KeyPressed(SDLK_SPACE, fighter);
					if (fighter->input.keyMap[SDLK_p])
						fighter->input.KeyPressed(SDLK_p, fighter);
				}
			}
		}
	}
}