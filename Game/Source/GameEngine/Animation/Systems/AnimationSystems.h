#pragma once
#include "Animation/AnimationClip.h"
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"

namespace Blz
{
	namespace Animation 
	{
		namespace System
		{
			AnimClip CreateAnimation(const uint16 startingIndex, const uint16 numTilesToAnimate);
			SpriteTileSheetComponent SetAnimation(SpriteTileSheetComponent fighterSprite, AnimClip& animation);
		}
	}
}
