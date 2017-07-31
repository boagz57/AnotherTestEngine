#pragma once
#include <GLM\detail\type_vec3.hpp>
#include "Graphics/Sprite.h"

class Fighter
{
public:
	Fighter(Blz::string imageFilePath, uint16 startingWorldPositionX, uint16 startingWorldPositionY);
	~Fighter();

	Sprite sprite;
	glm::vec3 localPosition{ 0.0f, 0.0f, 0.0f };
};