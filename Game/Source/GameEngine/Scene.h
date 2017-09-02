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

	Fighter* CreateAIFighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture);
	Fighter* CreatePlayerFighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture);

	Blz::SmallVector<Fighter> fighters;

private:
	uint16 numFighters = 0;
};

