#pragma once
#include "../GameEngine/Animation/AnimationClip.h"
#include "Containers/Map.h"

namespace Comp
{
	class Animation
	{
	public:
		Animation() = default;

		void AddAnimation(Blz::Animation::AnimationClip animation);
		void SetFinalAnimationPoseTo(uint16 animationID);
		Blz::Animation::AnimationClip* const GetCurrentAnimationPose() const;

	private:
		Blz::Map<uint16, Blz::Animation::AnimationClip> animationMap;
		Blz::Animation::AnimationClip* finalPose = nullptr;
	};
}