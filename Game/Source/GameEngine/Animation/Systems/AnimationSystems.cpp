#pragma once
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"
#include "AnimationSystems.h"

namespace Blz
{
	namespace Animation 
	{
		namespace System
		{
			Blz::Animation::AnimClip CreateAnimation(const uint16 lowIndexRange, const uint16 highIndexRange)
			{
				AnimClip animation;

				animation.lowIndexRange = lowIndexRange;
				animation.highIndexRange = highIndexRange;
				
				return animation;
			}

			SpriteTileSheetComponent SetAnimation(SpriteTileSheetComponent fighterSprite, AnimClip animation)
			{
				fighterSprite.SetUVs(animation.lowIndexRange);

				if (animation.currentIndex < animation.highIndexRange)
					animation.currentIndex++;
				else
					animation.currentIndex = 0;

				return fighterSprite;
			}
		}
	}
}