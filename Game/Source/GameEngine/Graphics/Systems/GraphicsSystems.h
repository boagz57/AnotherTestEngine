#pragma once
#include "../Texture.h"
#include "Components\Position.h"
#include "Components\SpriteTileSheet.h"
#include "Components\Sprite.h"

namespace Blz
{
	namespace Graphics 
	{
		namespace CompSystem
		{
			Comp::Position ConvertWorldUnitsToScreenPixels(Comp::Position fighterPositionToConvert, uint16 const windowWidth);
			Comp::SpriteTileSheet SetSpriteScreenLocation(Comp::Position fighterTransform, Comp::SpriteTileSheet fighterSprite);
			void SendFighterSpriteDataToGPU(Comp::SpriteTileSheet fighterSprite);
			void SendFighterSpriteDataToGPU(Comp::Sprite fighterSprite);
		}
	}
}