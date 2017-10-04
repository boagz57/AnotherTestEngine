#include <tuple>
#include "Fighter.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include <math.h>
#include "Scene.h"
#include "AnimationEngine.h"

namespace Blz
{
	namespace Animation
	{
		auto Engine::CreateAnimation(Fighter* const fighter, const uint16 startingIndex, const uint16 numTilesToAnimate, bool isDefault/* = fasle */) ->uint16
		{
			Blz::Animation::AnimationClip animation;

			animation.Init();
			animation.SetIndex(startingIndex);
			animation.SetTotalTilesForAnimation(numTilesToAnimate);

			fighter->animation.AddAnimation(animation, isDefault);

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
				//Set next animation frame
				[](Comp::Animation& fighterAnimation, Comp::SpriteTileSheet& fighterSprite, const Comp::Velocity& fighterVelocity, 
			   	   const Comp::Position& fighterPosition, const Comp::Input& input)
				{
					ec.AddContext("When trying to set next animation frame to display");

					Comp::Input fighterInput = input;
					
					if (std::abs(std::floor(fighterVelocity.GetCurrentState().x)) == 0.0f &&
						std::abs(std::floor(fighterPosition.GetCurrentPosition().y)) == c_groundLevel &&
						!fighterInput.IsKeyPressed())
					{
						fighterAnimation.SetFinalAnimation(fighterAnimation.GetDefaultAnimationID());
					}

					glm::vec4 newFrameUVs{ 0.0f };

					{//Calculate current uvs to display from sprite sheet
						uint16 currentFrame = fighterAnimation.GetCurrentAnimation().GetCurrentAnimationFrame();
						glm::ivec2 tileDimensions = fighterSprite.GetTileDimensions();

						uint16 tileXCoordinate = currentFrame % tileDimensions.x;
						uint16 tileYCoordinate = currentFrame / tileDimensions.x;

						newFrameUVs.x = tileXCoordinate / static_cast<sfloat>(tileDimensions.x);
						newFrameUVs.y = tileYCoordinate / static_cast<sfloat>(tileDimensions.y);
						newFrameUVs.w = 1.0f / tileDimensions.x;
						newFrameUVs.z = 1.0f / tileDimensions.y;
					};

					fighterSprite.SetUVCoordinates(newFrameUVs);

				}(fighter->animation, fighter->spriteSheet, fighter->velocity, fighter->position, fighter->input);
			}
		}
	}
}