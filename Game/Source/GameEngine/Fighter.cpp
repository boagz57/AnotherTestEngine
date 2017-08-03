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

void Fighter::SetPosition(int16 x, int16 y, int16 z)
{
	position.worldPosition = glm::vec3{ static_cast<sfloat>(x), static_cast<sfloat>(y), static_cast<sfloat>(z) };
}

void Fighter::AddToPosition(int16 x, int16 y, int16 z)
{
	position.worldPosition += glm::vec3{ static_cast<sfloat>(x), static_cast<sfloat>(y), static_cast<sfloat>(z) };
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
