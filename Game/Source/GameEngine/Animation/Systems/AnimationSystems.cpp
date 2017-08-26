#pragma once
#include "Containers/SmallVector.h"
#include "../../Components/Sprite.h"

namespace Blz
{
	namespace Animation 
	{
		namespace System
		{
			SpriteComponent SetAnimation(SpriteComponent fighterSprite, const uint16 c_LowIndexRange, const uint16 c_HighIndexRange)
			{
				static uint16 currentIndex;

				fighterSprite.SetUVs(currentIndex);

				if (currentIndex < c_HighIndexRange)
					currentIndex++;
				else
					currentIndex = 0;


				return fighterSprite;
			}
		}
	}
}