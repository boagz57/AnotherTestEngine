#pragma once
#include <GLM/vec3.hpp>
#include "Components/Position.h"
#include "Components/Sprite.h"
#include "Components/AABB.h"
#include "Components/Velocity.h"

class Fighter
{
public:
	Fighter(Blz::string imageFilePath, uint16 startingWorldPositionX, uint16 startingWorldPositionY);
	~Fighter();

	Sprite GetSprite();

	bool IsFighterControllable();
	void SetIfFighterShouldBeControllable(bool fighterControllable);

	PositionComponent position;
	VelocityComponent velocity;
	AABBComponent collisionBox;

	Sprite sprite;
	bool isControllable = false;
};