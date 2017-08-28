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
			animation = System::CreateAnimation(0, 15);
		}

		void AnimationManager::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				SpriteTileSheetComponent newSprite = System::SetAnimation(fighter.GetComponent<SpriteTileSheetComponent>(), animation);

				fighter.Insert(newSprite);
			}
		}
	}
}