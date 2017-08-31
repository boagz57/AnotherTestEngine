#pragma once
#include "../Texture.h"
#include "Components\Position.h"
#include "Components\SpriteTileSheet.h"

namespace Blz
{
	namespace Graphics 
	{
		namespace System
		{
			PositionComponent ConvertWorldUnitsToScreenPixels(PositionComponent fighterPositionToConvert, uint16 const windowWidth);
			SpriteTileSheetComponent SetSpriteScreenLocation(PositionComponent fighterTransform, SpriteTileSheetComponent fighterSprite, Texture textureToSet);
		}
	}
}