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
		auto ConvertWorldUnitsToScreenPixels(Comp::Position positionToConvert, uint16 windowWidth)->Comp::Position;
		auto ConvertWorldUnitsToScreenPixels(glm::vec2 positionToConvert, uint16 windowWidth)->glm::vec2;

		auto Engine::Init(Scene& scene, const Window& window) -> void
		{
			//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
			orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(window.width), 0.0f, static_cast<sfloat>(window.height));

			for (Fighter& fighter : scene.fighters)
			{
				Comp::Position actualScreenPixelPositions = ConvertWorldUnitsToScreenPixels(fighter.GetPosition(), window.width);

				Comp::SpriteTileSheet updatedSpriteLocation = [](Comp::SpriteTileSheet fighterSprite, Comp::Position fighterPosition) -> Comp::SpriteTileSheet
				{
					ec.AddContext("When setting sprite screen location");

					fighterSprite.SetScreenTargetLocationAndTileDimensions(fighterPosition.GetCurrentPosition().x, fighterPosition.GetCurrentPosition().y, glm::ivec2{ 8, 4 });

					return fighterSprite;
				}(fighter.GetSpriteSheet(), actualScreenPixelPositions);

				fighter.Insert(updatedSpriteLocation);
			}
		}

		auto Engine::Update(Scene& scene, ShaderProgram& shader, const Window& window) -> void
		{
			ec.AddContext("When updating graphics engine");

			GLuint transformationMatrixUniformLocation = shader.GetUniformLocation("transformationMatrix");

			GLuint uniformLocation = shader.GetUniformLocation("basicTexture");
			glUniform1i(uniformLocation, 0);

			GLuint vboID = 0;

			for (Fighter& fighter : scene.fighters)
			{
				++vboID;

				//Translate vertices of fighter to move him
				{
					glm::vec2 translationAmount = fighter.GetPosition().GetCurrentPosition() - fighter.originalPosition;

					glm::vec2 ConvertedTranslationPosition = ConvertWorldUnitsToScreenPixels(translationAmount, window.width);

					//Round values to nearest int value to avoid fractional values which can create distorted art work
					translationAmount.x = rint(ConvertedTranslationPosition.x);
					translationAmount.y = rint(ConvertedTranslationPosition.y);

					glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ ConvertedTranslationPosition.x, ConvertedTranslationPosition.y, 0.0f });
					glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));
				}

				glBindTexture(GL_TEXTURE_2D, fighter.GetSpriteSheet().GetTextureID());

				//Send updated Verts
				{
					glBindBuffer(GL_ARRAY_BUFFER, vboID);

					glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighter.GetSpriteSheet().GetVertexData().size()), &fighter.GetSpriteSheet().GetVertexData().front(), GL_DYNAMIC_DRAW);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));
				}

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//TODO: Remove zeroing out velocity from Renderer update. 
				Comp::Velocity vel = fighter.GetVelocity();
				vel.ZeroOut();

				fighter.Insert(vel);
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