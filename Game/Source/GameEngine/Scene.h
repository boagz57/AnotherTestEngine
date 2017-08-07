#pragma once
#include "../Universal/SmallVector.h"
#include "Fighter.h"


class Scene
{
public:
	Scene();
	~Scene();

	Fighter* CreateAIFighter(Blz::string imageFilePath, sfloat startingWorldPositionX, sfloat startingWorldPositionY);
	Fighter* CreatePlayerFighter(Blz::string imageFilePath, sfloat startingWorldPositionX, sfloat startingWorldPositionY);

	Blz::SmallVector<Fighter> fighters;

private:
	uint16 numFighters = 0;
};

