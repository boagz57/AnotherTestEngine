#include "Animation/AnimationClip.h"

namespace Blz
{
	namespace Animation
	{
		uint16 AnimationClip::id = 0;

		AnimationClip::AnimationClip()
		{
			this->id++;
		}

		void AnimationClip::SetIndex(uint16 index)
		{
			this->currentFrame = index;
			this->initalFrame = index;
		}

		void AnimationClip::SetTotalTilesForAnimation(uint16 numTiles)
		{
			this->numTilesToAnimate = numTiles;
		}

		void AnimationClip::IncrementIndex()
		{
			if (animationTime > 300.0f)
			{
				this->currentFrame++;

				if (this->currentFrame > (this->initalFrame + this->numTilesToAnimate))
				{
					this->currentFrame = this->initalFrame;
				}

				animationTime = 0;
			}

			animationTime++;
		}

		const uint16 AnimationClip::GetCurrentAnimationFrame() const
		{
			return currentFrame;
		}

		const uint16 AnimationClip::ID() const
		{
			return this->id;
		}
	}
}