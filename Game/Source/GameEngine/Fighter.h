#pragma once
#include <GLM/vec3.hpp>
#include "Components/Position.h"
#include "Components/Sprite.h"

class Fighter
{
public:
	Fighter(Blz::string imageFilePath, uint16 startingWorldPositionX, uint16 startingWorldPositionY);
	~Fighter();

	glm::vec3 GetPosition();
	void SetPosition(sfloat x, sfloat y, sfloat z);
	void AddToPosition(sfloat x, sfloat y, sfloat z);

	Sprite GetSprite();

	bool IsFighterControllable();
	void SetIfFighterShouldBeControllable(bool fighterControllable);

private:
	Position position;
	Sprite sprite;
	bool isControllable = false;
};