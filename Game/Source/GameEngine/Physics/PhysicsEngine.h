#pragma once
#include "../Scene.h"


namespace Blz::Physics
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		auto Init() -> void;
		auto Shutdown() -> void;
		auto Update(Scene& scene) -> void;
	};
}