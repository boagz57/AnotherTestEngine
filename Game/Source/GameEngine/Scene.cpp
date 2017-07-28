#include "Scene.h"

Scene::Scene()
{
	fighters.reserve(2);
}

Scene::~Scene()
{
}

void Scene::AddFighterToScene(Fighter& fighter)
{
	RUNTIME_ASSERT(fighters.size() != 3, "Creating too many fighters for game to handle!");
	fighters.push_back(fighter);
}
