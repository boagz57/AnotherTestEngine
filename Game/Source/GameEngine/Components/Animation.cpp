#include "Animation.h"

namespace Comp
{
	void Animation::AddAnimation(Blz::Animation::AnimationClip animation)
	{
		animationMap.insert(std::pair<uint16, Blz::Animation::AnimationClip>(animation.ID(), animation));
	}

	void Animation::SetFinalAnimationPoseTo(uint16 animationID)
	{
		finalPose = &this->animationMap[animationID];
		this->animationMap[animationID].IncrementIndex();
	}

	Blz::Animation::AnimationClip* const Animation::GetCurrentAnimationPose() const
	{
		return finalPose;
	}
}