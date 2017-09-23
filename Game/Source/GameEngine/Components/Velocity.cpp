#include "Velocity.h"

namespace Comp
{
	glm::vec2 const Velocity::GetCurrentState() const
	{
		return currentVelocity;
	}

	auto Velocity::Add(const sfloat x, const sfloat y) -> void
	{
		this->currentVelocity.x += x;
		this->currentVelocity.y += y;
	}

	auto Velocity::ZeroOutX() -> void
	{
		currentVelocity.x *= 0.0f;
	}

	auto Velocity::SetVelocity(sfloat x, sfloat y) -> void
	{
		this->currentVelocity.x = x;
		this->currentVelocity.y = y;
	}

	auto Velocity::SetVelocityY(sfloat y) -> void
	{
		this->currentVelocity.y = y;
	}

	auto Velocity::SetVelocityX(sfloat x) -> void
	{
		this->currentVelocity.x = x;
	}
}