#pragma once
#include "Containers/SmallVector.h"
#include "../../Components/Sprite.h"

namespace Blz
{
	namespace Animation 
	{
		namespace System
		{
			SpriteComponent SetAnimation(SpriteComponent fighterSprite, const uint16 lowIndexRange, const uint16 highIndexRange);
		}
	}
}
