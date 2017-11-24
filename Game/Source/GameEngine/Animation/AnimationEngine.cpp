#include <tuple>
#include "Fighter.h"
#include "Components/SpriteSheet.h"
#include "Components/Transform.h"
#include "Components/Velocity.h"
#include <math.h>
#include "Scene.h"
#include "AnimationEngine.h"

namespace Blz::Animation
{
	auto Engine::Init(Scene& scene) -> void
	{
	}

	auto Engine::Update(Scene& scene) -> void
	{
		for (Fighter* fighter : scene.fighters)
		{
			//Set next animation frame
			[](Comp::Animation& fighterAnimation, Comp::SpriteSheet& fighterSprite, const Comp::Velocity& fighterVelocity,
				const Comp::Position& fighterPosition, const Comp::Input& input)
			{
				Comp::Input fighterInput = input;

				if (std::abs(std::floor(fighterVelocity.GetCurrentState().x)) == 0.0f &&
					std::abs(std::floor(fighterPosition.GetCurrentPosition().y)) == c_groundLevel &&
					!fighterInput.IsKeyPressed())
				{
					fighterAnimation.SetCurrentAnimation(fighterAnimation.DefaultAnimation());
				}

				glm::vec4 newFrameUVs{ 0.0f };

				{//Calculate current uvs to display from sprite sheet
					uint16 currentFrame = fighterAnimation.CurrentAnimation().GetCurrentAnimationFrame();
					glm::ivec2 tileDimensions = fighterSprite.GetDimensions();

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