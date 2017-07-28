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

		for (uint16 i = 0; i < scene.fighters.size(); ++i)
		{
			if (IsKeyPressed(SDLK_w))
				scene.fighters.at(i).position += glm::vec3{ 0.0f, 0.1f, 0.0f };
			else if (IsKeyPressed(SDLK_s))
				scene.fighters.at(i).position += glm::vec3{ 0.0f, -0.1f, 0.0f };
			else if (IsKeyPressed(SDLK_a))
				scene.fighters.at(i).position += glm::vec3{ -0.1f, 0.0f, 0.0f };
			else if (IsKeyPressed(SDLK_d))
				scene.fighters.at(i).position += glm::vec3{ 0.1f, 0.0f, 0.0f };
		};
	}

	bool Input::IsKeyPressed(uint keyID)
	{
		return keyMap[keyID];
	}
}