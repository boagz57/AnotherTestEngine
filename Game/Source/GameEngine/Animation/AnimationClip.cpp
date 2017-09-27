#include "Animation/AnimationClip.h"

namespace Blz
{
	namespace Animation
	{
		uint16 AnimationClip::id = 0;

		auto AnimationClip::Init() -> void
		{
			++id;
		}

		auto AnimationClip::SetIndex(uint16 index) -> void
		{
			this->currentFrame = index;
			this->initalFrame = index;
		}

		auto AnimationClip::SetTotalTilesForAnimation(uint16 numTiles) -> void
		{
			this->numTilesToAnimate = numTiles;
		}

		auto AnimationClip::IncrementIndex() -> void
		{
			if (animationTime > 200.0f)
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

		auto AnimationClip::GetCurrentAnimationFrame() const -> const uint16
		{
			return currentFrame;
		}

		auto AnimationClip::ID() const -> const uint16
		{
			return this->id;
		}
	}
}