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

namespace Blz::Graphics
{
	auto Engine::Init(Scene& scene) -> void
	{
		//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
		orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(c_windowWidth), 0.0f, static_cast<sfloat>(c_windowHeight));

		{
			this->backGroundSprite.Init(scene.backgroundTexture);
			this->backGroundSprite.SetScreenPosition(static_cast<sfloat>(c_windowWidth/ 2), 120.0f);

			this->backgroundVBO = GL::InitializeGPUBuffer(backGroundSprite.GetVertexData());
		};

		uint16 i = 0;

		for (Fighter* fighter : scene.fighters)
		{
			{
				fighter->spriteSheet.SetScreenPosition(fighter->position.GetCurrentPosition().x, fighter->position.GetCurrentPosition().y);

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

	auto Engine::Update(Scene& scene, ShaderProgram& shader) -> void
	{
		GLuint transformationMatrixUniformLocation = shader.GetUniformLocation("transformationMatrix");

		GLuint uniformLocation = shader.GetUniformLocation("basicTexture");
		glUniform1i(uniformLocation, 0);

		GL::DrawTexture(backGroundSprite.GetVertexData(), backGroundSprite.GetTextureID(), backgroundVBO);

		uint16 i = 0;

		for (Fighter* fighter : scene.fighters)
		{
			{
				glm::vec2 translationAmount = fighter->position.GetCurrentPosition() - fighter->originalPosition;

				//Round final pixel positions so fractional pixel values can't cause distorted artwork
				translationAmount.x = rint(translationAmount.x);
				translationAmount.y = rint(translationAmount.y);

				glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ translationAmount.x, translationAmount.y, 0.0f });
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