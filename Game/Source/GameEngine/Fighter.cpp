#include <GLM/vec3.hpp>
#include "Fighter.h"
#include "ErrorContext.h"
#include "Components/Sprite.h"

Fighter::Fighter()
{}

Fighter::Fighter(Blz::string const imageFilePath, sfloat startPositionX, sfloat startPositionY) :
	sprite(imageFilePath, 200, 200)
{
	position.Add(startPositionX, startPositionY);
}

Fighter::~Fighter()
{}

bool Fighter::IsFighterControllable()
{
	return isControllable;
}

void Fighter::SetIfFighterShouldBeControllable(bool controllable)
{
	isControllable = controllable;
}
