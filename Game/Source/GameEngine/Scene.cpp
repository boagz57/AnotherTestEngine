#include "Scene.h"

Scene::Scene()
{
	fighters.reserve(2);
	fighterStartingPositions.reserve(2);
}

Scene::~Scene()
{
}

Fighter* Scene::CreateAIFighter(sfloat startingPositionX, sfloat startingPositionY)
{
	RUNTIME_ASSERT(this->numFighters <= 2, "Creating too many fighters for game to handle!");
	Fighter fighter(startingPositionX, startingPositionY);

	fighters.push_back(fighter);
	fighterStartingPositions.push_back(glm::vec2{ startingPositionX, startingPositionY });
	
	return &fighters.at(this->numFighters++);
}

Fighter* Scene::CreatePlayerFighter(sfloat startingPositionX, sfloat startingPositionY)
{
	RUNTIME_ASSERT(this->numFighters <= 2, "Creating too many fighters for game to handle!");
	Fighter fighter(startingPositionX, startingPositionY);

	fighter.SetIfFighterShouldBeControllable(true);

	fighters.push_back(fighter);
	fighterStartingPositions.push_back(glm::vec2{ startingPositionX, startingPositionY });
	
	return &fighters.at(this->numFighters++);
}
