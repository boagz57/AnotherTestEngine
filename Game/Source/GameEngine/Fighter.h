#pragma once
#include <GLM/vec3.hpp>
#include "Components/Sprite.h"
#include "Components/Position.h"
#include "Components/AABB.h"
#include "Components/Velocity.h"
#include "Components/Transform.h"

class Fighter
{
public:
	Fighter(Blz::string const imageFilePath, sfloat startingWorldPositionX, sfloat startingWorldPositionY);
	~Fighter();

	bool IsFighterControllable();
	void SetIfFighterShouldBeControllable(bool fighterControllable);

	PositionComponent position;
	VelocityComponent velocity;
	AABBComponent collisionBox;
	TransformComponent transform;
	Sprite sprite;

	bool isControllable = false;
};