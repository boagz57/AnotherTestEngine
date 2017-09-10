#pragma once

namespace Blz
{
	namespace Animation
	{
		class AnimationClip
		{
		public:
			AnimationClip();

			void SetIndex(uint16 index);
			void SetTotalTilesForAnimation(uint16 numTiles);
			void IncrementIndex();
			const uint16 GetCurrentAnimationFrame() const;
			const uint16 ID() const;

		private:
			sfloat animationTime = 0.0f;
			uint16 numTilesToAnimate = 0;
			uint16 initalFrame = 0;
			uint16 currentFrame = 0;
			static uint16 id;
		};
	}
}