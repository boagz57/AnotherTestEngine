#include "Fighter.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include "Scene.h"
#include "AnimationEngine.h"

namespace Blz
{
	namespace Animation
	{
		auto Engine::Init(Scene& scene) -> void
		{
		}

		auto Engine::Update(Scene& scene) -> void
		{
			ec.AddContext("When updating Animation engine");

			for (Fighter& fighter : scene.fighters)
			{
				//Set current spriteAnimation frame
				Comp::SpriteTileSheet newSprite = [](Comp::SpriteTileSheet& fighterSprite, const Comp::Animation& fighterAnimations) -> Comp::SpriteTileSheet
				{
					ec.AddContext("When trying to set next animation frame to display");

					uint16 currentFrame = fighterAnimations.GetCurrentAnimation().GetCurrentAnimationFrame();

					fighterSprite.SetUVs(currentFrame);

					return fighterSprite;
				}(fighter.GetSpriteSheet(), fighter.GetAnimation());

				fighter.Insert(newSprite);
			}
		}
	}
}