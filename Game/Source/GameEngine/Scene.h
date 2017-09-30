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

	auto AddFighter(Fighter* fighter) -> void;

	Blz::SmallVector<Fighter*> fighters;

private:
	uint16 numFighters = 0;
};

