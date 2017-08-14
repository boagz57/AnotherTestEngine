#include "Fighter.h"
#include "Components/Sprite.h"

Fighter::Fighter()
{}

Fighter::Fighter(sfloat startPositionX, sfloat startPositionY) 
{
	originalPosition.x = startPositionX;
	originalPosition.y = startPositionY;
}

Fighter::~Fighter()
{}

bool Fighter::IsFighterControllable()
{
	return isControllable;
}

void Fighter::SetFighterToBeControllable()
{
	isControllable = true;
}
