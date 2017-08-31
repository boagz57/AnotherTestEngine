#include "Fighter.h"
#include "Components\SpriteTileSheet.h"
#include "Components\Transform.h"
#include "GameWorldSystems.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace System
		{
			SpriteTileSheetComponent SetSpriteWidthAndHeight(SpriteTileSheetComponent fighterSprite, sfloat const spriteWidth, sfloat const spriteHeight)
			{
				fighterSprite.SetWidthAndHeight(spriteWidth, spriteHeight);
				return fighterSprite;
			}
		}
	}
}