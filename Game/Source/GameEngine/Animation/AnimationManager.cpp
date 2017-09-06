#include "Fighter.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Scene.h"
#include "Systems/AnimationSystems.h"
#include "AnimationManager.h"

namespace Blz
{
	namespace Animation
	{
		void AnimationManager::Init(Scene& scene)
		{
			uint16 walkingUp = CreateAnimation(0, 7);
		}

		void AnimationManager::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				
			}
		}

		uint16 AnimationManager::CreateAnimation(const uint16 startingIndex, const uint16 numTilesToAnimate)
		{
			AnimClip animation;

			animation.SetIndex(startingIndex);
			animation.SetTotalTilesForAnimation(numTilesToAnimate);

			this->animationMap[animation.ID()] = animation;

			return animation.ID();
		}

		void AnimationManager::PlayAnimation(uint16 animationToPlay)
		{
			finalPose = this->animationMap[animationToPlay];
		}
	}
}