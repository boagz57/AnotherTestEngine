#pragma once
#include <SDL.h>
#include "Fighter.h"
#include "Containers/UnorderedMap.h"
#include "../Scene.h"

namespace Blz::Input
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