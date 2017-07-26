#pragma once
#include <GLM\detail\type_vec3.hpp>
#include "Graphics/Sprite.h"

namespace Blz { namespace Graphics { class Renderer; } }

class Fighter
{
public:
	Fighter(Blz::string imageFilePath);
	~Fighter();

private:
	friend class Blz::Graphics::Renderer;

	Sprite GetSprite();
	Sprite sprite;

	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
};