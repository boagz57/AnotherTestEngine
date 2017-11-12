#pragma once
#include <SDL_events.h>

class Scene;

namespace Blz::Input
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		auto Update(Scene& scene) -> void;

	private:
		SDL_Event evnt{};
	};
}