#include <GL\glew.h>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <math.h>
#include <GLM\vec2.hpp>
#include "ShaderProgram.h"
#include "OpenGL\OpenGL.h"
#include "../Components/SpriteSheet.h"
#include "Texture.h"
#include "../Vector3D.h"
#include "GraphicsEngine.h"
#include "../Scene.h"
#include "../Fighter.h"

//Helper functions
static auto ConvertWorldUnitsToScreenPixels(Comp::Position positionToConvert, uint16 windowWidth)->Comp::Position;
static auto ConvertWorldUnitsToScreenPixels(glm::vec2 positionToConvert, uint16 windowWidth)->glm::vec2;

namespace Blz
{
	namespace Graphics
	{
		auto Engine::Init(Scene& scene, const Window& window) -> void
		{
			//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
			orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(window.width), 0.0f, static_cast<sfloat>(window.height));

			{
				ec.AddContext("When setting background image location");

				this->backGroundSprite.Init(scene.backgroundTexture);
				this->backGroundSprite.SetScreenPosition(static_cast<sfloat>(window.width / 2), 120.0f);

				this->backgroundVBO = GL::InitializeGPUBuffer(backGroundSprite.GetVertexData());
			};

			uint16 i = 0;

			for (Fighter* fighter : scene.fighters)
			{
				{
					ec.AddContext("When setting fighter sprite intial screen location and UVs");

					Comp::Position convertedFighterPosition = ConvertWorldUnitsToScreenPixels(fighter->position, window.width);

					fighter->spriteSheet.SetScreenPosition(convertedFighterPosition.GetCurrentPosition().x, convertedFighterPosition.GetCurrentPosition().y);

					{//Set initial sprite UV location
						glm::ivec2 spriteSheetDimensions = fighter->spriteSheet.GetDimensions();
						glm::vec4 initialSpriteUVs;

						uint16 xTile = 0 % spriteSheetDimensions.x;
						uint16 yTile = 0 / spriteSheetDimensions.y;

						initialSpriteUVs.x = xTile / static_cast<sfloat>(spriteSheetDimensions.x);
						initialSpriteUVs.y = yTile / static_cast<sfloat>(spriteSheetDimensions.y);
						initialSpriteUVs.w = 1.0f / spriteSheetDimensions.x;
						initialSpriteUVs.z = 1.0f / spriteSheetDimensions.y;

						fighter->spriteSheet.SetUVCoordinates(initialSpriteUVs);
					}

					GLuint fighterVBOID = GL::InitializeGPUBuffer(fighter->spriteSheet.GetVertexData());
					this->fighterVBOs.at(i) = fighterVBOID;

					++i;
				};
			};
		}

		auto Engine::Update(Scene& scene, ShaderProgram& shader, const Window& window) -> void
		{
			ec.AddContext("When updating graphics engine");

			GLuint transformationMatrixUniformLocation = shader.GetUniformLocation("transformationMatrix");

			GLuint uniformLocation = shader.GetUniformLocation("basicTexture");
			glUniform1i(uniformLocation, 0);

			GL::DrawTexture(backGroundSprite.GetVertexData(), backGroundSprite.GetTextureID(), backgroundVBO);

			uint16 i = 0;

			for (Fighter* fighter : scene.fighters)
			{
				{
					ec.AddContext("When translating fighter verticies to move fighter");

					glm::vec2 translationAmount = fighter->position.GetCurrentPosition() - fighter->originalPosition;

					glm::vec2 ConvertedTranslationPosition = ConvertWorldUnitsToScreenPixels(translationAmount, window.width);

					//Round final pixel positions so fractional pixel values can't cause distorted artwork
					ConvertedTranslationPosition.x = rint(ConvertedTranslationPosition.x);
					ConvertedTranslationPosition.y = rint(ConvertedTranslationPosition.y);

					glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ ConvertedTranslationPosition.x, ConvertedTranslationPosition.y, 0.0f });
					glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));
				}

				GL::DrawTexture(fighter->spriteSheet.GetVertexData(), fighter->spriteSheet.GetTextureID(), this->fighterVBOs.at(i));

				//Zero out velocity to prevent fighter sliding
				//TODO: Remove from rendering code
				fighter->velocity.ZeroOutX();
			}

			++i;
		}
	}
}

auto ConvertWorldUnitsToScreenPixels(Comp::Position position, uint16 windowWidth) -> Comp::Position
{
	ec.AddContext("When converting my world units to screen pixels");

	if (windowWidth == 1920)
	{
		position.MultiplyBy(12, 12);
	}
	else if (windowWidth == 1280)
	{
		position.MultiplyBy(8, 8);
	}

	return position;
}

auto ConvertWorldUnitsToScreenPixels(glm::vec2 positionToConvert, uint16 windowWidth) -> glm::vec2
{
	ec.AddContext("When converting my world units to screen pixels");

	if (windowWidth == 1920)
	{
		positionToConvert *= 12;
	}
	else if (windowWidth == 1280)
	{
		positionToConvert *= 8;
	}

	return positionToConvert;
}