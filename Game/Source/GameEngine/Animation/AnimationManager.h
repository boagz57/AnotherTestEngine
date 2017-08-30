#pragma once
#include "AnimationClip.h"
#include "Containers/Map.h"
#include "Scene.h"

namespace Blz
{
	namespace Animation
	{
		enum class AnimationState
		{
			WALKINGUP,
			WALKINGRIGHT,
			IDLE
		};

		class AnimationManager
		{
		public:
			AnimationManager() = default;
			~AnimationManager() = default;

			void Init(Scene& scene);
			void Update(Scene& scene);

		private:
			Blz::Map<AnimationState, AnimClip> animationMap;
		};
	}
}
