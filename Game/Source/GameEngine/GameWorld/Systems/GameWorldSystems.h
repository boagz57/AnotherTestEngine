#pragma once
#include "Fighter.h"
#include "../../Components/Position.h"
#include "../../Components/SpriteTileSheet.h"
#include "../../Components/Sprite.h"
#include "Graphics/Texture.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace CompSystem
		{
			Comp::SpriteTileSheet SetSpriteTexture(Comp::SpriteTileSheet fighterSprite, Blz::Graphics::Texture texture);
			Comp::Sprite SetSpriteTexture(Comp::Sprite fighterSprite, Blz::Graphics::Texture texture);
			Comp::SpriteTileSheet SetSpriteWidthAndHeight(Comp::SpriteTileSheet fighterSprite, const sfloat spriteWidth, const sfloat spriteHeight);
		}
	}
}
