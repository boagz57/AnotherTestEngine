#include "Scene.h"
#include "Math.h"

Scene::Scene()
{
	fighters.reserve(2);
}

auto Scene::CreateFighter(sfloat startingPositionX, sfloat startingPositionY, Blz::Graphics::Texture texture) -> Fighter*
{
	ec.AddContext("When Creating a fighter");

	startingPositionX = rint(startingPositionX);
	startingPositionY = rint(startingPositionY);

	RUNTIME_ASSERT(startingPositionX <= 160.0f && startingPositionY <= 90.0f, "Cannot position fighter outside specified design unit range of 160 units in x or 90 units in y");
	RUNTIME_ASSERT(startingPositionX >= 0.0f && startingPositionY >= 0.0f, "Cannot position fighter outside specified design unit range of 0 units in x or 0 units in y");

	Fighter fighter(startingPositionX, startingPositionY, texture);

	fighters.push_back(fighter);
	
	return &fighters.at(this->numFighters++);
}
