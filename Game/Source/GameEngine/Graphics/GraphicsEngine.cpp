#include <GL\glew.h>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <math.h>
#include <GLM\vec2.hpp>
#include "ShaderProgram.h"
#include "SystemHelpers\SystemHelpers.h"
#include "../Components/SpriteTileSheet.h"
#include "Texture.h"
#include "../Vector3D.h"
#include "GraphicsEngine.h"
#include "../Scene.h"
#include "../Fighter.h"


namespace Blz
{
	namespace Graphics
	{
		//Helper functions
		static auto ConvertWorldUnitsToScreenPixels(Comp::Position positionToConvert, uint16 windowWidth)->Comp::Position;
		static auto ConvertWorldUnitsToScreenPixels(glm::vec2 positionToConvert, uint16 windowWidth)->glm::vec2;

		auto Engine::Init(Scene& scene, const Window& window) -> void
		{
			//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
			orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(window.width), 0.0f, static_cast<sfloat>(window.height));

			for (Fighter* fighter : scene.fighters)
			{
				Comp::Position actualScreenPixelPositions = ConvertWorldUnitsToScreenPixels(fighter->position, window.width);

				[](Comp::SpriteTileSheet& fighterSprite, Comp::Position& fighterPosition) -> void
				{
					ec.AddContext("When setting sprite screen location");

					fighterSprite.Init(fighterPosition.GetCurrentPosition().x, 
						fighterPosition.GetCurrentPosition().y, glm::ivec2{ 10, 4 });

					SysHelper::InitializeGLBuffer(fighterSprite.GetVertexData());

				}(fighter->spriteSheet, actualScreenPixelPositions);
			}
		}

		auto Engine::Update(Scene& scene, ShaderProgram& shader, const Window& window) -> void
		{
			ec.AddContext("When updating graphics engine");

			GLuint transformationMatrixUniformLocation = shader.GetUniformLocation("transformationMatrix");

			GLuint uniformLocation = shader.GetUniformLocation("basicTexture");
			glUniform1i(uniformLocation, 0);

			GLuint vboID = 0;

			for (Fighter* fighter : scene.fighters)
			{
				++vboID;

				//Translate vertices of fighter to move him
				{
					glm::vec2 translationAmount = fighter->position.GetCurrentPosition() - fighter->originalPosition;

					glm::vec2 ConvertedTranslationPosition = ConvertWorldUnitsToScreenPixels(translationAmount, window.width);

					//Round final pixel positions so fractional pixel values can't cause distorted artwork
					ConvertedTranslationPosition.x = rint(ConvertedTranslationPosition.x);
					ConvertedTranslationPosition.y = rint(ConvertedTranslationPosition.y);

					glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ ConvertedTranslationPosition.x, ConvertedTranslationPosition.y, 0.0f });
					glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));
				}

				glBindTexture(GL_TEXTURE_2D, fighter->spriteSheet.GetTextureID());

				glBindBuffer(GL_ARRAY_BUFFER, vboID);

				//Send down new text coords to draw
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighter->spriteSheet.GetVertexData().size()), &fighter->spriteSheet.GetVertexData().front(), GL_DYNAMIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//Zero out velocity to prevent fighter sliding
				//TODO: Remove from rendering code
				fighter->velocity.ZeroOutX();
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
				positionToConvert*= 12;
			}
			else if (windowWidth == 1280)
			{
				positionToConvert*= 8;
			}

			return positionToConvert;
		}
	}
}