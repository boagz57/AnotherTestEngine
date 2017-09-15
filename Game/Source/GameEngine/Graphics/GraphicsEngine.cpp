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
		auto Engine::Init(Scene& scene, Window& window) -> void
		{
			//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
			orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(window.width), 0.0f, static_cast<sfloat>(window.height));

			for (Fighter& fighter : scene.fighters)
			{
				//Convert my world units to actual screen pixels
				Comp::Position ConvertedPixelPosition = [](Comp::Position positionCoordsToConvert, const uint16 windowWidth) -> Comp::Position
				{
					ec.AddContext("When converting my world units to screen pixels");

					if (windowWidth == 1920)
					{
						positionCoordsToConvert.MultiplyBy(12, 12);
					}
					else if (windowWidth == 1280)
					{
						positionCoordsToConvert.MultiplyBy(8, 8);
					}

					return positionCoordsToConvert;
				}(fighter.GetPosition(), window.width);


				//Set new sprite screen location based on new coordinates
				Comp::SpriteTileSheet updatedSpriteLocation = [](Comp::SpriteTileSheet fighterSprite, Comp::Position fighterPosition) -> Comp::SpriteTileSheet
				{
					ec.AddContext("When setting sprite screen location");

					fighterSprite.SetScreenTargetLocationAndTileDimensions(fighterPosition.GetCurrentPosition().x, fighterPosition.GetCurrentPosition().y, glm::ivec2{ 8, 4 });

					SysHelper::InitializeGLBuffer(fighterSprite.GetVertexData());

					return fighterSprite;
				}(fighter.GetSpriteSheet(), ConvertedPixelPosition);

				fighter.Insert(updatedSpriteLocation);
			}
		}

		auto Engine::Update(Scene& scene, ShaderProgram& shader) -> void
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

					//Round values to nearest int value to avoid fractional values which can create distorted art work
					translationAmount.x = rint(translationAmount.x);
					translationAmount.y = rint(translationAmount.y);

					glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ translationAmount.x, translationAmount.y, 0.0f });
					glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));
				}

				glBindTexture(GL_TEXTURE_2D, fighter.GetSpriteSheet().GetTextureID());

				//Send new 
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
				Comp::Transform trans = fighter.GetTransform();
				trans.ZeroOut();
				vel.ZeroOut();
				
				fighter.Insert(vel);
				fighter.Insert(trans);
			}
		}
	}
}