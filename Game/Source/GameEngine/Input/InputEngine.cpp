#include <SDL.h>
#include "Systems\InputSystems.h"
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
			}
		}
	}
}