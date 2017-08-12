#pragma once
#include <GLM\vec2.hpp>
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
	Blz::SmallVector<glm::vec2> fighterStartingPositions;

private:
	uint16 numFighters = 0;
};

