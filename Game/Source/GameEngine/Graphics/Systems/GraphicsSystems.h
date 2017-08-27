#pragma once
#include "../Texture.h"
#include "Components\Transform.h"
#include "Components\SpriteTileSheet.h"

namespace Blz
{
	namespace Graphics 
	{
		namespace System
		{
			TransformComponent ConvertWorldUnitsToScreenPixels(TransformComponent fighterTransformToConvert, uint16 const windowWidth);
			SpriteTileSheetComponent SetSpriteScreenLocation(TransformComponent fighterTransform, SpriteTileSheetComponent fighterSprite, Texture textureToSet);
		}
	}
}