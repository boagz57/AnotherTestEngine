#pragma once

class Fighter;
class Scene;

namespace Blz::Physics
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		auto Init(Scene& scene) -> void;
		auto Shutdown() -> void;
		auto Update(Scene& scene, sfloat deltaTime) -> void;

	private:
		Fighter* fighter1{ nullptr };
		Fighter* fighter2{ nullptr };
	};
}