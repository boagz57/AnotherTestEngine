#include "Scene.h"

Scene::Scene()
{
	fighters.reserve(2);
}

Scene::~Scene()
{
}

Fighter* Scene::CreateFighter()
{
	RUNTIME_ASSERT(fighters.size() != 3, "Creating too many fighters for game to handle!");
	Fighter fighter("CharImage.png");

	fighters.push_back(fighter);
	
	return &fighters.at(numFighters++);
}