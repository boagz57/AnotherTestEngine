#pragma once
#include "AnimationClip.h"
#include "Containers/Vector.h"
#include "Scene.h"

namespace Blz
{
	namespace Animation
	{
		class AnimationManager
		{
		public:
			AnimationManager() = default;
			~AnimationManager() = default;

			void Init(Scene& scene);
			void Update(Scene& scene);

			uint16 CreateAnimation(const uint16 startingIndex, const uint16 numTilesToAnimate);
			void PlayAnimation(uint16 animationToPlay);

		private:
			Blz::Map<uint16, AnimClip> animationMap;
			AnimClip* finalPose;
		};
	}
}
