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
			PositionComponent Blz::GameWorld::System::SetFighterStartingPosition(PositionComponent fighterPosition, glm::vec2 fighterStartingPositions)
			{
				fighterPosition.SetPosition(fighterStartingPositions.x, fighterStartingPositions.y);

				return fighterPosition;
			}

			SpriteTileSheetComponent SetSpriteWidthAndHeight(SpriteTileSheetComponent fighterSprite, sfloat const spriteWidth, sfloat const spriteHeight)
			{
				fighterSprite.SetWidthAndHeight(spriteWidth, spriteHeight);
				return fighterSprite;
			}
		}
	}
}