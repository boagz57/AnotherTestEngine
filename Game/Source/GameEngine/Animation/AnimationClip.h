#pragma once

namespace Blz
{
	namespace Animation
	{
		class AnimationClip
		{
		public:
			AnimationClip();

			auto SetIndex(uint16 index) -> void;
			auto SetTotalTilesForAnimation(uint16 numTiles) -> void;
			auto IncrementIndex() -> void;
			auto GetCurrentAnimationFrame() const -> const uint16;
			auto ID() const -> const uint16;

		private:
			sfloat animationTime = 0.0f;
			uint16 numTilesToAnimate = 0;
			uint16 initalFrame = 0;
			uint16 currentFrame = 0;
			static uint16 id;
		};
	}
}