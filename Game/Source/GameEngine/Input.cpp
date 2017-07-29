#include <SDL.h>
#include "Scene.h"
#include "Input.h"

namespace Blz
{
	Input::Input()
	{
	}

	Input::~Input()
	{
	}

	void Input::ProcessInput(Scene& scene)
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

		for (Fighter& fighter : scene.fighters)
		{
			if (IsKeyPressed(SDLK_w))
				fighter.localPosition += glm::vec3{ 0.0f, 0.1f, 0.0f };
			else if (IsKeyPressed(SDLK_s))
				fighter.localPosition += glm::vec3{ 0.0f, -0.1f, 0.0f };
			else if (IsKeyPressed(SDLK_a))
				fighter.localPosition += glm::vec3{ -0.1f, 0.0f, 0.0f };
			else if (IsKeyPressed(SDLK_d))
				fighter.localPosition += glm::vec3{ 0.1f, 0.0f, 0.0f };
		};
	}

	bool Input::IsKeyPressed(uint keyID)
	{
		return keyMap[keyID];
	}
}