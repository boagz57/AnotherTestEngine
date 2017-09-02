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
			AnimClip walkingUp = CompSystem::CreateAnimation(0, 7);
			AnimClip walkingRight= CompSystem::CreateAnimation(8, 7);
			AnimClip idle = CompSystem::CreateAnimation(24, 7);

			animationMap[AnimationState::WALKINGUP] = walkingUp;
			animationMap[AnimationState::WALKINGRIGHT] = walkingRight;
			animationMap[AnimationState::IDLE] = idle;
		}

		void AnimationManager::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				Comp::SpriteTileSheet newSprite;

				if (fighter.GetComponent<Comp::Velocity>().GetCurrentState().x > 0.0f)
				{
					newSprite = CompSystem::SetAnimation(fighter.GetComponent<Comp::SpriteTileSheet>(), animationMap.at(AnimationState::WALKINGRIGHT));
				}
				else if (fighter.GetComponent<Comp::Velocity>().GetCurrentState().y > 0.0f)
				{
					newSprite = CompSystem::SetAnimation(fighter.GetComponent<Comp::SpriteTileSheet>(), animationMap.at(AnimationState::WALKINGUP));
				}
				else
				{
					newSprite = CompSystem::SetAnimation(fighter.GetComponent<Comp::SpriteTileSheet>(), animationMap.at(AnimationState::IDLE));
				}

				fighter.Insert(newSprite);
			}
		}
	}
}