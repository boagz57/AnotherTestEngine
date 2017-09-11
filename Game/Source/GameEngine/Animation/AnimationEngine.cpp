#include "Fighter.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Scene.h"
#include "Systems/AnimationSystems.h"
#include "AnimationEngine.h"

namespace Blz
{
	namespace Animation
	{
		void Engine::Init(Scene& scene)
		{
		}

		void Engine::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				Comp::SpriteTileSheet newSprite = CompSystem::SetAnimationFrameToDisplay(fighter.GetComponent<Comp::SpriteTileSheet>(), fighter.GetComponent<Comp::Animation>());

				fighter.Insert(newSprite); 
			}
		}
	}
}