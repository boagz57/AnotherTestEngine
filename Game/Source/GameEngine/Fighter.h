#pragma once
#include <memory>
#include <GLM/vec3.hpp>
#include "Graphics/Texture.h"
#include "Containers/Map.h"
#include "Components/Animation.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Velocity.h"
#include "Components/Input.h"
#include "Components/Transform.h"
#include "Components\Position.h"

class Fighter 
{
public:
	Fighter() = default;
	Fighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture);
	~Fighter() = default;

	Comp::Transform transform;
	Comp::Velocity velocity;
	Comp::SpriteTileSheet spriteSheet;
	Comp::Animation animation;
	Comp::Position position;
	Comp::Input input;

	glm::vec2 originalPosition{ 160.0f, 0.0f };
};
