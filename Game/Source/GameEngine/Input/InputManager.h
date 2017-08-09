#pragma once
#include <SDL.h>
#include "../../Universal/UnorderedMap.h"
#include "../Scene.h"

namespace Blz
{
	namespace Input
	{
		class InputManager
		{
		public:
			void Update(Scene& scene);

		private:
			Blz::UMap<uint, bool> keyMap;
			SDL_Event evnt;
		};
	}
}