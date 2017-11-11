#pragma once
#include <GLM/vec2.hpp>

namespace Comp
{
	class Velocity
	{
	public:
		Velocity() = default;

		glm::vec2 const GetCurrentState() const;
		void Add(const sfloat x, const sfloat y);
		auto ZeroOutX() -> void;
		auto ZeroOutY() -> void;
		auto SetVelocity(sfloat x, sfloat y) -> void;
		auto SetVelocityY(sfloat y) -> void;
		auto SetVelocityX(sfloat x) -> void;

	private:
		glm::vec2 currentVelocity{};
	};
}