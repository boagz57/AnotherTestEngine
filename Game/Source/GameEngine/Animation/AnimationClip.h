#pragma once

namespace Blz
{
	namespace Animation
	{
		class AnimClip
		{
		public:
			AnimClip();

			void SetIndex(uint16 index);
			void SetTotalTilesForAnimation(uint16 numTiles);
			void IncrementIndex();
			const uint16 GetCurrentClipIndex() const;
			const uint16 ID() const;

		private:
			sfloat animationTime = 0.0f;
			uint16 numTilesToAnimate = 0;
			uint16 startingIndex = 0;
			uint16 currentIndex = 0;
			static uint16 id;
		};
	}
}