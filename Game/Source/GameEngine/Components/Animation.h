#pragma once
#include "../GameEngine/Animation/AnimationClip.h"
#include "Containers/Map.h"

namespace Comp
{
	class Animation
	{
	public:
		Animation() = default;

		void AddAnimation(Blz::Animation::AnimationClip animation, bool makeDefault);
		void SetFinalAnimation(uint16 const animationID);
		Blz::Animation::AnimationClip const GetCurrentAnimation() const;
		auto GetDefaultAnimationID() -> uint16 const { return defaultAnimationID; };

	private:
		Blz::Map<const uint16, Blz::Animation::AnimationClip> animationMap;
		uint16 defaultAnimationID{};
		Blz::Animation::AnimationClip finalAnimation{};
	};
}