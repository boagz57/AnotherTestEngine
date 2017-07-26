#pragma once
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
};