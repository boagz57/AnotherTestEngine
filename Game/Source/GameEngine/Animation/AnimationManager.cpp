#include "Fighter.h"
#include "AnimationClip.h"
#include "AnimationManager.h"

namespace Blz
{
	namespace Animation
	{
		auto Manager::CreateAnimation(Fighter* fighter, uint16 startingIndex, uint16 numTilesToAnimate) -> uint16
		{
			Blz::Animation::AnimationClip animation;

			animation.SetIndex(startingIndex);
			animation.SetTotalTilesForAnimation(numTilesToAnimate);

			fighter->animation.AddAnimation(animation);

			return animation.ID();
		}

		auto Manager::PlayAnimation(Fighter* fighter, uint16 const animationID) -> void
		{
			fighter->animation.SetFinalAnimation(animationID);
		}
	}
}