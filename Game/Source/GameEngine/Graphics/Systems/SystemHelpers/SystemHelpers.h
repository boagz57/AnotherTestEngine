#pragma once
#include "Components\Sprite.h"
#include "Components\SpriteTileSheet.h"

namespace Blz
{
	namespace Graphics
	{
		namespace SysHelper
		{
			void SendFighterSpriteDataToGPU(Comp::SpriteTileSheet fighterSprite);
			void SendFighterSpriteDataToGPU(Comp::Sprite fighterSprite);
		}
	}
}