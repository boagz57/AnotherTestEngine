#include <GLM/vec3.hpp>
#include "Fighter.h"
#include "ErrorContext.h"
#include "Components/Sprite.h"

Fighter::Fighter(Blz::string imageFilePath, uint16 startPositionX, uint16 startPositionY) 
{
	Blz::Err::ErrorContext ec("When initializing fighter character with image", imageFilePath);

	sprite.Init(startPositionX, startPositionY, 200, 200, imageFilePath);
}

Fighter::~Fighter()
{
}

glm::vec3 Fighter::GetPosition()
{
	return position.worldPosition;
}

void Fighter::SetPosition(sfloat x, sfloat y, sfloat z)
{
	position.worldPosition = glm::vec3{ x, y, z };
}

void Fighter::AddToPosition(sfloat x, sfloat y, sfloat z)
{
	position.worldPosition += glm::vec3{ x, y, z };
}

Sprite Fighter::GetSprite()
{
	return sprite;
}

bool Fighter::IsFighterControllable()
{
	return isControllable;
}

void Fighter::SetIfFighterShouldBeControllable(bool controllable)
{
	isControllable = controllable;
}
