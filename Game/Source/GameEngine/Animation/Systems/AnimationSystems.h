#pragma once
#include "Animation/AnimationClip.h"
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"
#include "../../Components/Animation.h"

namespace Blz
{
	namespace Animation 
	{
		namespace CompSystem
		{
			Comp::SpriteTileSheet SetCurentAnimationPose(Comp::SpriteTileSheet fighterSprite, Comp::Animation fighterAnimations);
		}
	}
}
