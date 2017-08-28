#include "Animation/AnimationClip.h"

namespace Blz
{
	namespace Animation
	{
		void AnimClip::SetIndex(uint16 index)
		{
			this->currentIndex = index;
			this->startingIndex = index;
		}

		void AnimClip::SetTotalTilesForAnimation(uint16 numTiles)
		{
			this->numTilesToAnimate = numTiles;
		}

		void AnimClip::IncrementIndex()
		{
			if (animationTime > 300.0f)
			{
				this->currentIndex++;

				if (this->currentIndex > (this->startingIndex + this->numTilesToAnimate))
				{
					this->currentIndex = this->startingIndex;
				}

				animationTime = 0;
			}

			animationTime++;
		}

		const uint16 AnimClip::GetCurrentClipIndex() const
		{
			return currentIndex;
		}
	}
}