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

			auto Bind(const int32 key, Fighter* const fighter, std::function<void(Fighter*)> movementFunction) -> void;

			auto Update(Scene& scene) -> void;

		private:
			Blz::Map<uint, bool> keyMap;
			SDL_Event evnt;
		};
	}
}