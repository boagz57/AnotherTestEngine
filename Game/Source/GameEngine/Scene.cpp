#include "Scene.h"
#include "Math.h"

Scene::Scene()
{
	fighters.reserve(2);
}

auto Scene::AddFighter(Fighter* p_fighter) -> void 
{
	ec.AddContext("When adding a fighter");

	fighters.push_back(p_fighter); 
}
