#include "Fighter.h"
#include "AnimationClip.h"
#include "AnimationManager.h"

namespace Blz
{
	namespace Animation
	{
		auto Manager::CreateAnimation(Fighter* const fighter, const uint16 startingIndex, const uint16 numTilesToAnimate) -> uint16
		{
			Blz::Animation::AnimationClip animation;

			animation.Init();
			animation.SetIndex(startingIndex);
			animation.SetTotalTilesForAnimation(numTilesToAnimate);

			fighter->animation.AddAnimation(animation);

			return animation.ID();
		}

		auto Manager::PlayAnimation(Fighter* const fighter, uint16 const animationID) -> void
		{
			fighter->animation.SetFinalAnimation(animationID);
		}
	}
}