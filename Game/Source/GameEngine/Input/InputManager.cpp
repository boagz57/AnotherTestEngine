#include <SDL.h>
#include "Systems\InputSystems.h"
#include "../Fighter.h"
#include "InputManager.h"

namespace Blz
{
	namespace Input
	{

		void InputManager::SetFighterToBeControllable(Fighter* fighter)
		{
			Comp::Input input = fighter->GetComponent<Comp::Input>();
			input.MakeFighterControllable();

			fighter->Insert(input);
		}

		void InputManager::Update(Scene& scene)
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