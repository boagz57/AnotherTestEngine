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
	RUNTIME_ASSERT(startingPositionX <= 160.0f && startingPositionY <= 90.0f, "Cannot position fighter outside specified world unit range of 160 units in x or 90 units in y");

	Fighter fighter(startingPositionX, startingPositionY);

	fighters.push_back(fighter);
	fighterStartingPositions.push_back(glm::vec2{ startingPositionX, startingPositionY });
	
	return &fighters.at(this->numFighters++);
}

Fighter* Scene::CreatePlayerFighter(sfloat startingPositionX, sfloat startingPositionY)
{
	RUNTIME_ASSERT(this->numFighters <= 2, "Creating too many fighters for game to handle!");
	RUNTIME_ASSERT(startingPositionX <= 160.0f && startingPositionY <= 90.0f, "Cannot position fighter outside specified design unit range of 160 units in x or 90 units in y");

	Fighter fighter(startingPositionX, startingPositionY);

	fighter.SetFighterToBeControllable();

	fighters.push_back(fighter);
	fighterStartingPositions.push_back(glm::vec2{ startingPositionX, startingPositionY });
	
	return &fighters.at(this->numFighters++);
}
