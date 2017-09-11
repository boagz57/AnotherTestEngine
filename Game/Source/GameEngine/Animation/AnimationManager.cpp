#include "Fighter.h"
#include "AnimationClip.h"
#include "AnimationManager.h"

namespace Blz
{
	namespace Animation
	{
		uint16 Manager::CreateAnimation(Fighter* fighter, uint16 startingIndex, uint16 numTilesToAnimate)
		{
			Blz::Animation::AnimationClip animation;

			animation.SetIndex(startingIndex);
			animation.SetTotalTilesForAnimation(numTilesToAnimate);

			fighter->animation.AddAnimation(animation);

			return animation.ID();
		}

		void Manager::PlayAnimation(Fighter* fighter, uint16 const animationID)
		{
			fighter->animation.SetFinalAnimation(animationID);
		}
	}
}