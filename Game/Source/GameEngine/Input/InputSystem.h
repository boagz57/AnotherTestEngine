#pragma once
#include <SDL.h>
#include "../../Universal/UnorderedMap.h"
#include "../Scene.h"

namespace Blz
{
	class InputSystem
	{
	public:
		void ProcessInput(Scene& scene);

	private:
		Blz::UMap<uint, bool> keyMap;
		SDL_Event evnt;
	};
}