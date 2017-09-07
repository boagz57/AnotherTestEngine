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
	const T GetComponent() const;

	template<class T>
	void Insert(T comp);

	bool IsFighterControllable();
	void SetFighterToBeControllable();

	glm::vec2 originalPosition{ 160.0f, 0.0f };

private:
	bool isControllable = false;
};

template<class T>
inline const T Fighter::GetComponent() const
{
	return this->ComponentHolder<T>::component;
}

template<class T>
inline void Fighter::Insert(T comp)
{
	this->ComponentHolder<T>::component = comp;
}