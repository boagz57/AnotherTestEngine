#pragma once
#include "../../Components/Sprite.h"

namespace Blz
{
	namespace Animation 
	{
		namespace System
		{
			SpriteComponent SetAnimation(SpriteComponent fighterSprite, uint16 index)
			{
				fighterSprite.SetUVs(index);

				return fighterSprite;
			}
		}
	}
}