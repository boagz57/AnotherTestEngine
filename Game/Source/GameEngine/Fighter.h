#pragma once
#include <memory>
#include <GLM/vec3.hpp>
#include "../Universal/Map.h"
#include "Components\ComponentHolder.h"
#include "Components/Sprite.h"
#include "Components/Velocity.h"
#include "Components/Transform.h"

class Fighter :
	public ComponentHolder<TransformComponent>,
	public ComponentHolder<VelocityComponent>
{
public:
	Fighter();
	Fighter(Blz::string const imageFilePath, sfloat startingWorldPositionX, sfloat startingWorldPositionY);
	~Fighter();

	template<class T>
	inline T GetComponent();

	template<class T>
	inline void Insert(T comp);

	bool IsFighterControllable();
	void SetIfFighterShouldBeControllable(bool fighterControllable);

	glm::vec2 originalPosition{ 0.0f, 0.0f };
	SpriteComponent sprite;

	bool isControllable = false;
};

template<class T>
T Fighter::GetComponent() 
{
	return this->ComponentHolder<T>::component;
}

template<class T>
void Fighter::Insert(T comp)
{
	this->ComponentHolder<T>::component = comp;
}