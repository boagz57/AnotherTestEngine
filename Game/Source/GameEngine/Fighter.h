#pragma once
#include <GLM/vec3.hpp>
#include "Components/Sprite.h"
#include "Components/AABB.h"
#include "Components/Velocity.h"
#include "Components/Transform.h"

class Fighter
{
public:
	Fighter();
	Fighter(Blz::string const imageFilePath, sfloat startingWorldPositionX, sfloat startingWorldPositionY);
	~Fighter();

	bool IsFighterControllable();
	void SetIfFighterShouldBeControllable(bool fighterControllable);

	VelocityComponent velocity;
	AABBComponent collisionBox;
	TransformComponent transform;
	glm::vec2 originalPosition{ 0.0f, 0.0f };
	Sprite sprite;

	bool isControllable = false;
};