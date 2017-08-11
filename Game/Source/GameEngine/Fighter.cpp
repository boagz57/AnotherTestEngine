#include <GLM/vec3.hpp>
#include "Fighter.h"
#include "ErrorContext.h"
#include "Components/Sprite.h"

Fighter::Fighter()
{}

Fighter::Fighter(Blz::string const imageFilePath, sfloat startPositionX, sfloat startPositionY) :
	sprite(imageFilePath, 200, 200)
{
	componentMap[0] = new TransformComponent(glm::vec2{ 0.0f, 0.0f });
	componentMap[1] = new VelocityComponent();
	originalPosition.x = startPositionX;
	originalPosition.y = startPositionY;
}

Fighter::~Fighter()
{}

bool Fighter::IsFighterControllable()
{
	return isControllable;
}

void Fighter::SetIfFighterShouldBeControllable(bool controllable)
{
	isControllable = controllable;
}

void Fighter::Insert(Component* component)
{
	componentMap.erase(component->ID());
	componentMap[component->ID()] = component;
}