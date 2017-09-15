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
		void SetFinalAnimation(uint16 const animationID);
		Blz::Animation::AnimationClip const GetCurrentAnimation() const;

	private:
		Blz::Map<const uint16, Blz::Animation::AnimationClip> animationMap;
		Blz::Animation::AnimationClip finalAnimation;
	};
}