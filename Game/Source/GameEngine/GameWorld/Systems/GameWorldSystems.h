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
		namespace System
		{
			SpriteTileSheetComponent SetSpriteTexture(SpriteTileSheetComponent fighterSprite, Blz::Graphics::Texture texture);
			SpriteComponent SetSpriteTexture(SpriteComponent fighterSprite, Blz::Graphics::Texture texture);
			SpriteTileSheetComponent SetSpriteWidthAndHeight(SpriteTileSheetComponent fighterSprite, const sfloat spriteWidth, const sfloat spriteHeight);
		}
	}
}
