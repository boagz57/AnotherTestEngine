#pragma once
#include "../Universal/SmallVector.h"
#include "Fighter.h"

class Scene
{
public:
	Scene();
	~Scene();

	Fighter* CreateAIFighter(Blz::string spriteImageFilePath, uint16 startingWorldPositionX, uint16 startingWorldPositionY);
	Fighter* CreatePlayerFighter(Blz::string spriteImageFilePath, uint16 startingWorldPositionX, uint16 startingWorldPositionY);

	Blz::SmallVector<Fighter> fighters;

private:
	uint16 numFighters = 0;
};

