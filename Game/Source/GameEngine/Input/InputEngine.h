#pragma once
#include <SDL.h>
#include "Fighter.h"
#include "Containers/UnorderedMap.h"
#include "../Scene.h"

/*
	Input System Responsible for the Gathering of input and changing only those components which do not directly effect Fighter. So This system would
	never manipulate a Fighter's position directly for exmaple. 
*/

namespace Blz
{
	namespace Input
	{
		class Engine
		{
		public:
			Engine() = default;
			~Engine() = default;

			auto Update(Scene& scene) -> void;

		private:
			Blz::Map<uint, bool> keyMap;
			SDL_Event evnt;
		};
	}
}