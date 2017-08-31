#include "Fighter.h"
#include "Components/SpriteTileSheet.h"

Fighter::Fighter(sfloat startPositionX, sfloat startPositionY) 
{
	ComponentHolder<PositionComponent>::component.SetPosition(startPositionX, startPositionY);
}

bool Fighter::IsFighterControllable()
{
	return isControllable;
}

void Fighter::SetFighterToBeControllable()
{
	isControllable = true;
}
