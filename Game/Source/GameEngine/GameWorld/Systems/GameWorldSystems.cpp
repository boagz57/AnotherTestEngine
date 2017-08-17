#include "Fighter.h"
#include "Components\Sprite.h"
#include "Components\Transform.h"
#include "GameWorldSystems.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace System
		{
			TransformComponent Blz::GameWorld::System::SetFighterStartingPosition(TransformComponent fighterPosition, glm::vec2 fighterStartingPositions)
			{
				fighterPosition.SetPosition(fighterStartingPositions.x, fighterStartingPositions.y);

				return fighterPosition;
			}

			SpriteComponent SetSpriteWidthAndHeight(SpriteComponent fighterSprite, sfloat const spriteWidth, sfloat const spriteHeight)
			{
				fighterSprite.SetWidthAndHeight(spriteWidth, spriteHeight);
				return fighterSprite;
			}
		}
	}
}