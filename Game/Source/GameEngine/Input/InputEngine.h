#pragma once
#include <SDL.h>
#include "Fighter.h"
#include "Containers/UnorderedMap.h"
#include "../Scene.h"

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
			SDL_Event evnt;
		};
	}
}