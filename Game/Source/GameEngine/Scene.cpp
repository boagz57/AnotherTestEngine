#include "Scene.h"

Scene::Scene()
{
	fighters.reserve(2);
}

Scene::~Scene()
{
}

Fighter* Scene::CreateFighter(Blz::string spriteImage, uint16 startingPositionX, uint16 startingPositionY)
{
	RUNTIME_ASSERT(this->numFighters <= 2, "Creating too many fighters for game to handle!");
	Fighter fighter(spriteImage, startingPositionX, startingPositionY);

	fighters.push_back(fighter);
	
	return &fighters.at(this->numFighters++);
}