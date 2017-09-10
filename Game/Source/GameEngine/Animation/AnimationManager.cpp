#include "Fighter.h"
#include "AnimationClip.h"
#include "AnimationManager.h"

namespace Blz
{
	namespace Animation
	{
		uint16 Manager::CreateAnimation(Fighter* fighter, uint16 startingIndex, uint16 numTilesToAnimate)
		{
			Comp::Animation fighterAnimations = fighter->GetComponent<Comp::Animation>();

			Blz::Animation::AnimationClip animation;

			animation.SetIndex(startingIndex);
			animation.SetTotalTilesForAnimation(numTilesToAnimate);

			fighterAnimations.AddAnimation(animation);

			fighter->Insert(fighterAnimations);

			return animation.ID();
		}

		void Manager::PlayAnimation(Fighter* fighter, uint16 const animationID)
		{
			Comp::Animation fighterAnimations = fighter->GetComponent<Comp::Animation>();
			fighterAnimations.SetFinalAnimationPoseTo(animationID);

			fighter->Insert(fighterAnimations);
		}
	}
}