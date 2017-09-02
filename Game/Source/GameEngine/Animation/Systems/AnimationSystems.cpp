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
			Blz::Animation::AnimClip CreateAnimation(const uint16 startingIndex, const uint16 numTilesToAnimate)
			{
				AnimClip animation;

				animation.SetIndex(startingIndex);
				animation.SetTotalTilesForAnimation(numTilesToAnimate);
				
				return animation;
			}

			Comp::SpriteTileSheet SetAnimation(Comp::SpriteTileSheet fighterSprite, AnimClip& animation)
			{
				fighterSprite.SetUVs(animation.GetCurrentClipIndex());
				animation.IncrementIndex();

				return fighterSprite;
			}
		}
	}
}