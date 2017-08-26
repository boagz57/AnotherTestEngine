#include "Fighter.h"
#include "Components/Sprite.h"
#include "Scene.h"
#include "Systems/AnimationSystems.h"
#include "AnimationManager.h"

namespace Blz
{
	namespace Animation
	{
		void AnimationManager::Init(Scene & scene)
		{
		}

		void AnimationManager::Update(Scene & scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				SpriteComponent newSprite = System::SetAnimation(fighter.GetComponent<SpriteComponent>(), 7);

				fighter.Insert(newSprite);
			}
		}
	}
}