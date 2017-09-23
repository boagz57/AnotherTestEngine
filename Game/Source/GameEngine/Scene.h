#pragma once
#include <GLM\vec2.hpp>
#include "Graphics\Texture.h"
#include "Containers/SmallVector.h"
#include "Fighter.h"

class Scene
{
public:
	Scene();
	~Scene() = default;

	auto CreateFighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture) -> Fighter*;

	Blz::SmallVector<Fighter> fighters;

private:
	uint16 numFighters = 0;
};

