#pragma once
#include "../Scene.h"


namespace Blz::Physics
{
	class Engine
	{
	public:
		struct Components
		{
			Comp::Velocity velocity;
			Comp::Position position;
			Comp::Movement movement;
		};

		Engine() = default;
		~Engine() = default;

		auto Init() -> void;
		auto Shutdown() -> void;
		auto Update(Scene& scene) -> Components;
	};
}