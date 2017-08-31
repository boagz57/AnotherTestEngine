#pragma once
#include <memory>
#include <GLM/vec3.hpp>
#include "Containers/Map.h"
#include "Components\ComponentHolder.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Velocity.h"
#include "Components/Transform.h"
#include "Components\Position.h"

class Fighter :
	public ComponentHolder<TransformComponent>,
	public ComponentHolder<VelocityComponent>,
	public ComponentHolder<SpriteTileSheetComponent>,
	public ComponentHolder<PositionComponent>
{
public:
	Fighter() = default;
	Fighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY);
	~Fighter() = default;

	template<class T>
	T GetComponent();

	template<class T>
	void Insert(T comp);

	bool IsFighterControllable();
	void SetFighterToBeControllable();

	glm::vec2 originalPosition{ 0.0f, 0.0f };

private:
	bool isControllable = false;
};

template<class T>
inline T Fighter::GetComponent() 
{
	return this->ComponentHolder<T>::component;
}

template<class T>
inline void Fighter::Insert(T comp)
{
	this->ComponentHolder<T>::component = comp;
}