#pragma once
#include <GLM\detail\type_vec3.hpp>
#include "Graphics/Sprite.h"

namespace Blz { namespace Graphics { class Renderer; } }
namespace Blz { class Input; }

class Fighter
{
public:
	Fighter(Blz::string imageFilePath, uint16 startingWorldPositionX, uint16 startingWorldPositionY);
	~Fighter();

	glm::vec3 GetLocalPosition();

private:
	friend class Blz::Graphics::Renderer;
	friend class Blz::Input;

	Sprite sprite;
	glm::vec3 localPosition{ 0.0f, 0.0f, 0.0f };
};