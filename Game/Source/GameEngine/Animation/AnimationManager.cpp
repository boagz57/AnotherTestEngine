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
			AnimClip walkingUp = System::CreateAnimation(0, 7);
			AnimClip walkingRight= System::CreateAnimation(8, 7);
			AnimClip idle = System::CreateAnimation(24, 7);

			animationMap[AnimationState::WALKINGUP] = walkingUp;
			animationMap[AnimationState::WALKINGRIGHT] = walkingRight;
			animationMap[AnimationState::IDLE] = idle;
		}

		void AnimationManager::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				SpriteTileSheetComponent newSprite;

				if (fighter.GetComponent<VelocityComponent>().GetCurrentState().x > 0.0f)
				{
					newSprite = System::SetAnimation(fighter.GetComponent<SpriteTileSheetComponent>(), animationMap.at(AnimationState::WALKINGRIGHT));
				}
				else if (fighter.GetComponent<VelocityComponent>().GetCurrentState().y > 0.0f)
				{
					newSprite = System::SetAnimation(fighter.GetComponent<SpriteTileSheetComponent>(), animationMap.at(AnimationState::WALKINGUP));
				}
				else
				{
					newSprite = System::SetAnimation(fighter.GetComponent<SpriteTileSheetComponent>(), animationMap.at(AnimationState::IDLE));
				}

				fighter.Insert(newSprite);
			}
		}
	}
}