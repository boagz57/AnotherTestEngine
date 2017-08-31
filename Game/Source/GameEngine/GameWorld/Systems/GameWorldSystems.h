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
			PositionComponent SetFighterStartingPosition(PositionComponent fighterPosition, glm::vec2 fighterStartingPositions);
			SpriteTileSheetComponent SetSpriteWidthAndHeight(SpriteTileSheetComponent fighterSprite, const sfloat spriteWidth, const sfloat spriteHeight);
		}
	}
}
