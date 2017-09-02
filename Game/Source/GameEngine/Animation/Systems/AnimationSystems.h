#pragma once
#include "Animation/AnimationClip.h"
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"

namespace Blz
{
	namespace Animation 
	{
		namespace CompSystem
		{
			AnimClip CreateAnimation(const uint16 startingIndex, const uint16 numTilesToAnimate);
			Comp::SpriteTileSheet SetAnimation(Comp::SpriteTileSheet fighterSprite, AnimClip& animation);
		}
	}
}
