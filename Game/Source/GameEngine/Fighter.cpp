#include "Fighter.h"
#include "Components/SpriteTileSheet.h"

Fighter::Fighter(sfloat startPositionX, sfloat startPositionY) 
{
	originalPosition.x = startPositionX;
	originalPosition.y = startPositionY;
}

bool Fighter::IsFighterControllable()
{
	return isControllable;
}

void Fighter::SetFighterToBeControllable()
{
	isControllable = true;
}
