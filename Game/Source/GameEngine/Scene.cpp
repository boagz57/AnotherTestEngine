#include "Scene.h"
#include "Math.h"

Scene::Scene()
{
	fighters.reserve(2);
}

auto Scene::AddFighter(Fighter* p_fighter) -> void 
{
	fighters.push_back(p_fighter); 
}

auto Scene::SetBackground(Blz::Graphics::Texture backgroundTexture) -> void
{
	this->backgroundTexture = backgroundTexture;
}
