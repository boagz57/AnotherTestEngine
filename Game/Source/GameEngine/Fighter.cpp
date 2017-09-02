#include "Fighter.h"
#include "Components/SpriteTileSheet.h"

Fighter::Fighter(sfloat startPositionX, sfloat startPositionY) 
{
	ComponentHolder<Comp::Position>::component.SetPosition(startPositionX, startPositionY);
}

bool Fighter::IsFighterControllable()
{
	return isControllable;
}

void Fighter::SetFighterToBeControllable()
{
	isControllable = true;
}
