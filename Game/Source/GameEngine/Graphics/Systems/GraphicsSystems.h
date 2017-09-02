#pragma once
#include "../Texture.h"
#include "Components\Position.h"
#include "Components\SpriteTileSheet.h"
#include "Components\Sprite.h"

namespace Blz
{
	namespace Graphics 
	{
		namespace System
		{
			PositionComponent ConvertWorldUnitsToScreenPixels(PositionComponent fighterPositionToConvert, uint16 const windowWidth);
			SpriteTileSheetComponent SetSpriteScreenLocation(PositionComponent fighterTransform, SpriteTileSheetComponent fighterSprite);
			void SendFighterSpriteDataToGPU(SpriteTileSheetComponent fighterSprite);
			void SendFighterSpriteDataToGPU(SpriteComponent fighterSprite);
		}
	}
}