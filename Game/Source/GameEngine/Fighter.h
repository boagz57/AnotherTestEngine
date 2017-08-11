#pragma once
#include <memory>
#include <GLM/vec3.hpp>
#include "../Universal/Map.h"
#include "Components\Component.h"
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

	AABBComponent collisionBox;
	glm::vec2 originalPosition{ 0.0f, 0.0f };
	Sprite sprite;

	void Insert(Component* component);

	bool isControllable = false;
	Blz::Map<uint16, Component*> componentMap;
};
