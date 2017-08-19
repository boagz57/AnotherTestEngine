#pragma once
#include <GLM\vec2.hpp>
#include "Containers/SmallVector.h"
#include "Fighter.h"

class Scene
{
public:
	Scene();
	~Scene() = default;

	Fighter* CreateAIFighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY);
	Fighter* CreatePlayerFighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY);

	Blz::SmallVector<Fighter> fighters;
	Blz::SmallVector<glm::vec2> fighterStartingPositions;

private:
	uint16 numFighters = 0;
};

