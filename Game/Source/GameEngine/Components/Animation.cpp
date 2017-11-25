#include "Animation.h"

namespace Comp
{
	void Animation::AddAnimation(Blz::Animation::AnimationClip animation, bool makeDefault)
	{
		if (makeDefault)
			defaultAnimationID = animation.ID();

		animationMap.insert(std::pair<const uint16, Blz::Animation::AnimationClip>(animation.ID(), animation));
	}

	void Animation::SetCurrentAnimation(uint16 const animationID)
	{
		BGZ_RUNTIME_ASSERT(animationMap.find(animationID) != animationMap.end(), "Animation not found!");
		BGZ_RUNTIME_ASSERT(animationMap.find(defaultAnimationID) != animationMap.end(), "No default animation specified for fighter!");

		currentAnimation = animationMap.find(animationID)->second;
		animationMap.at(animationID).CycleAnimation();
	}

	Blz::Animation::AnimationClip const Animation::CurrentAnimation() const
	{
		return currentAnimation;
	}
}