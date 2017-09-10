#pragma once
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"
#include "../../Components/Animation.h"
#include "AnimationSystems.h"

namespace Blz
{
	namespace Animation 
	{
		namespace CompSystem
		{
			Comp::SpriteTileSheet SetCurentAnimationPose(Comp::SpriteTileSheet fighterSprite, Comp::Animation fighterAnimations)
			{
				fighterSprite.SetUVs(fighterAnimations.GetCurrentAnimationPose()->GetCurrentAnimationFrame());

				return fighterSprite;
			}
		}
	}
}