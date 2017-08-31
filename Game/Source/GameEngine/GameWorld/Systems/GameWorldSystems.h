#pragma once
#include "Fighter.h"
#include "../../Components/Position.h"
#include "../../Components/SpriteTileSheet.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace System
		{
			SpriteTileSheetComponent SetSpriteWidthAndHeight(SpriteTileSheetComponent fighterSprite, const sfloat spriteWidth, const sfloat spriteHeight);
		}
	}
}
