#pragma once

class Scene;

namespace Blz::Animation
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		auto Init(Scene& scene) -> void;
		auto Update(Scene& scene) -> void;
	};
}
