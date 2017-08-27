#include "Fighter.h"
#include "Components/SpriteTileSheet.h"
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
		}

		void AnimationManager::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				AnimClip walkingAnimation = System::CreateAnimation(0, 16);
				SpriteTileSheetComponent newSprite = System::SetAnimation(fighter.GetComponent<SpriteTileSheetComponent>(), walkingAnimation);

				fighter.Insert(newSprite);
			}
		}
	}
}