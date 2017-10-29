#include "Fighter.h"
#include "../AnimationClip.h"
#include "AnimationGameLogic.h"

namespace Blz::Animation
{
	auto GameLogic::CreateAnimation(Fighter* const fighter, const uint16 startingIndex, const uint16 numTilesToAnimate, bool isDefault /*= false*/) ->uint16
	{
		Blz::Animation::AnimationClip animation;

		animation.Init();
		animation.SetIndex(startingIndex);
		animation.SetTotalTilesForAnimation(numTilesToAnimate);

		fighter->animation.AddAnimation(animation, isDefault);

		return animation.ID();
	}

	auto GameLogic::PlayAnimation(Fighter * const fighter, uint16 const animationID) -> void
	{
		fighter->animation.SetCurrentAnimation(animationID);
	}
}