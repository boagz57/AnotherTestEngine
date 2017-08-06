#include "Scene.h"

Scene::Scene()
{
	fighters.reserve(2);
}

Scene::~Scene()
{
}

Fighter* Scene::CreateAIFighter(Blz::string imageFilePath, sfloat startingPositionX, sfloat startingPositionY)
{
	RUNTIME_ASSERT(this->numFighters <= 2, "Creating too many fighters for game to handle!");
	Fighter fighter(imageFilePath, startingPositionX, startingPositionY);

	fighters.push_back(fighter);
	
	return &fighters.at(this->numFighters++);
}

Fighter* Scene::CreatePlayerFighter(Blz::string imageFilePath, sfloat startingPositionX, sfloat startingPositionY)
{
	RUNTIME_ASSERT(this->numFighters <= 2, "Creating too many fighters for game to handle!");
	Fighter fighter(imageFilePath, startingPositionX, startingPositionY);

	fighter.SetIfFighterShouldBeControllable(true);

	fighters.push_back(fighter);

	return &fighters.at(this->numFighters++);
}
