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

		auto Engine::CreateAnimation(Fighter* const fighter, const uint16 startingIndex, const uint16 numTilesToAnimate) ->uint16
		{
			Blz::Animation::AnimationClip animation;

			animation.Init();
			animation.SetIndex(startingIndex);
			animation.SetTotalTilesForAnimation(numTilesToAnimate);

			fighter->animation.AddAnimation(animation);

			return animation.ID();
		}

		auto Engine::PlayAnimation(Fighter* const fighter, uint16 const animationID) -> void
		{
			fighter->animation.SetFinalAnimation(animationID);
		}

		auto Engine::Init(Scene& scene) -> void
		{
		}

		auto Engine::Update(Scene& scene) -> void
		{
			ec.AddContext("When updating Animation engine");

			for (Fighter* fighter : scene.fighters)
			{
				//Set current spriteAnimation frame
				Comp::SpriteTileSheet newAnimatedSprite = [](Comp::SpriteTileSheet fighterSprite, const Comp::Animation& fighterAnimations) -> Comp::SpriteTileSheet
				{
					ec.AddContext("When trying to set next animation frame to display");

					glm::vec4 newFrameUVs{ 0.0f };

					{//Calculate current uvs to display 
						uint16 currentFrame = fighterAnimations.GetCurrentAnimation().GetCurrentAnimationFrame();
						glm::ivec2 tileDimensions = fighterSprite.GetTileDimensions();

						uint16 tileXCoordinate = currentFrame % tileDimensions.x;
						uint16 tileYCoordinate = currentFrame / tileDimensions.x;

						newFrameUVs.x = tileXCoordinate / static_cast<sfloat>(tileDimensions.x);
						newFrameUVs.y = tileYCoordinate / static_cast<sfloat>(tileDimensions.y);
						newFrameUVs.w = 1.0f / tileDimensions.x;
						newFrameUVs.z = 1.0f / tileDimensions.y;
					}

					fighterSprite.SetUVCoordinates(newFrameUVs);

					return fighterSprite;
				}(fighter->spriteSheet, fighter->animation);

				fighter->spriteSheet = newAnimatedSprite;
			}
		}
	}
}