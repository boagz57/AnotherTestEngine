#pragma once
#include <memory>
#include <GLM/vec3.hpp>
#include "Graphics/Texture.h"
#include "Containers/Map.h"
#include "Components\ComponentHolder.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Velocity.h"
#include "Components/Transform.h"
#include "Components\Position.h"

class Fighter :
	public ComponentHolder<Comp::Transform>,
	public ComponentHolder<Comp::Velocity>,
	public ComponentHolder<Comp::SpriteTileSheet>,
	public ComponentHolder<Comp::Position>
{
public:
	Fighter() = default;
	Fighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture);
	~Fighter() = default;

	template<class T>
	T GetComponent();

	template<class T>
	void Insert(T comp);

	bool IsFighterControllable();
	void SetFighterToBeControllable();

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