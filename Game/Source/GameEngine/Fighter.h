#pragma once
#include <GLM\detail\type_vec3.hpp>
#include "Graphics/Sprite.h"

namespace Blz { namespace Graphics { class Renderer; } }
namespace Blz { class Input; }

class Fighter
{
public:
	Fighter(Blz::string imageFilePath);
	~Fighter();

protected:
	glm::vec3 GetPosition();

private:
	friend class Blz::Graphics::Renderer;
	friend class Blz::Input;

	Sprite sprite;
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
};