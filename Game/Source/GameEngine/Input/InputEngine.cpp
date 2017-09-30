#include <SDL.h>
#include "../Fighter.h"
#include "InputEngine.h"

namespace Blz
{
	namespace Input
	{

		auto Engine::Bind(const int32 key, Fighter* const fighter, std::function<void(Fighter*)> movementFunction) -> void
		{
			fighter->input.MakeFighterControllable();
			fighter->input.SetKeyBinding(key, movementFunction);
		}

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

			for (Fighter* fighter : scene.fighters)
			{
				{//Take action on input
					if (fighter->input.IsFighterControllable())
					{
						if (this->keyMap[SDLK_d])
							fighter->input.KeyPressed(SDLK_d, fighter);
						if (this->keyMap[SDLK_a])
							fighter->input.KeyPressed(SDLK_a, fighter);
						if (this->keyMap[SDLK_SPACE])
							fighter->input.KeyPressed(SDLK_SPACE, fighter);
						if (this->keyMap[SDLK_p])
							fighter->input.KeyPressed(SDLK_p, fighter);
					}
				}
			}
		}
	}
}