#include <SDL.h>
#include "Input.h"

namespace Blz
{
	Input::Input()
	{
	}

	Input::~Input()
	{
	}

	void Input::ProcessInput()
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
			LOG("Hellllllo");
	}

	bool Input::IsKeyPressed(uint keyID)
	{
		return keyMap[keyID];
	}
}