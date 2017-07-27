#include <SDL.h>
#include "Fighter.h"
#include "Input.h"

namespace Blz
{
	Input::Input()
	{
	}

	Input::~Input()
	{
	}

	void Input::ProcessInput(Fighter& fighter)
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

		if (IsKeyPressed(SDLK_w))
			fighter.position += glm::vec3{ 0.0f, 0.1f, 0.0f };
		else if (IsKeyPressed(SDLK_s))
			fighter.position += glm::vec3{ 0.0f, -0.1f, 0.0f };
		else if (IsKeyPressed(SDLK_a))
			fighter.position += glm::vec3{ -0.1f, 0.0f, 0.0f };
		else if (IsKeyPressed(SDLK_d))
			fighter.position += glm::vec3{ 0.1f, 0.0f, 0.0f };
	}

	bool Input::IsKeyPressed(uint keyID)
	{
		return keyMap[keyID];
	}
}