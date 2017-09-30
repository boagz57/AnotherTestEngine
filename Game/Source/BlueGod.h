#pragma once
#include "Fighter.h"

class BlueGod : public Fighter
{
public:
	BlueGod() = default;

	auto Init(sfloat startPositionX, sfloat startPositionY, Blz::Graphics::Texture texture) -> void;

	Comp::Transform const GetTransform() const { return GetTransform(); };
	Comp::SpriteTileSheet const GetSpriteSheet() const { return Fighter::GetSpriteSheet(); };
	Comp::Animation const GetAnimation() const { return Fighter::GetAnimation(); };
	Comp::Input GetInput() const { return Fighter::GetInput(); };
	Comp::Velocity const GetVelocity() const { return Fighter::GetVelocity(); };
	Comp::Position const GetPosition() const { return Fighter::GetPosition(); };
	Comp::Movement const GetMovement() const { return Fighter::GetMovement(); };
};
