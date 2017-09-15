#include "Animation.h"

namespace Comp
{
	void Animation::AddAnimation(Blz::Animation::AnimationClip animation)
	{
		animationMap.insert(std::pair<const uint16, Blz::Animation::AnimationClip>(animation.ID(), animation));
	}

	void Animation::SetFinalAnimation(uint16 const animationID)
	{
		RUNTIME_ASSERT(animationMap.find(animationID) != animationMap.end(), "Animation not found!");

		finalAnimation = animationMap.find(animationID)->second;
		animationMap.at(animationID).IncrementIndex();
	}

	Blz::Animation::AnimationClip const Animation::GetCurrentAnimation() const
	{
		return finalAnimation;
	}
}