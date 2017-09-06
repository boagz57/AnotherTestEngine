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
			Comp::SpriteTileSheet SetAnimation(Comp::SpriteTileSheet fighterSprite, AnimClip& animation);
		}
	}
}
