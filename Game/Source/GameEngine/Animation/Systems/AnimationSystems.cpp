#pragma once
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"
#include "AnimationSystems.h"

namespace Blz
{
	namespace Animation 
	{
		namespace CompSystem
		{
			Comp::SpriteTileSheet SetAnimation(Comp::SpriteTileSheet fighterSprite, AnimClip animation)
			{
				fighterSprite.SetUVs(animation.GetCurrentClipIndex());
				animation.IncrementIndex();

				return fighterSprite;
			}
		}
	}
}