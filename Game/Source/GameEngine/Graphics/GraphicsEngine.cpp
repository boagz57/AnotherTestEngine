#include <GL\glew.h>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <math.h>
#include <GLM\vec2.hpp>
#include "ShaderProgram.h"
#include "../Components/SpriteTileSheet.h"
#include "Texture.h"
#include "../Vector3D.h"
#include "GraphicsEngine.h"
#include "Systems\GraphicsSystems.h"
#include "../Scene.h"
#include "../Fighter.h"

namespace Blz
{
	namespace Graphics
	{
		void Engine::Init(Scene& scene, Window& window)
		{
			//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
			orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(window.width), 0.0f, static_cast<sfloat>(window.height));

			for (Fighter& fighter : scene.fighters)
			{
				Comp::Position ConvertedPixelPosition = CompSystem::ConvertWorldUnitsToScreenPixels(fighter.position ,window.width);

				Comp::SpriteTileSheet UpdatedSpriteLocation = CompSystem::SetSpriteScreenLocation(ConvertedPixelPosition, fighter.spriteSheet);

				fighter.spriteSheet = UpdatedSpriteLocation;
			}
		}

		void Engine::Update(Scene& scene, ShaderProgram& shader)
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
					glm::vec2 translationAmount = fighter.position.GetCurrentPosition() - fighter.originalPosition;

					//Round values to nearest int value to avoid fractional values which can create distorted art work
					translationAmount.x = rint(translationAmount.x);
					translationAmount.y = rint(translationAmount.y);

					glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ translationAmount.x, translationAmount.y, 0.0f });
					glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));
				}

				glBindTexture(GL_TEXTURE_2D, fighter.spriteSheet.GetTextureID());

				//Send new 
				{
					glBindBuffer(GL_ARRAY_BUFFER, vboID);

					glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighter.spriteSheet.GetVertexData().size()), &fighter.spriteSheet.GetVertexData().front(), GL_DYNAMIC_DRAW);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));
				}

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//TODO: Remove zeroing out velocity from Renderer update. 
				Comp::Velocity vel = fighter.velocity;
				Comp::Transform trans = fighter.transform;
				trans.ZeroOut();
				vel.ZeroOut();
				
				fighter.velocity = vel;
				fighter.transform = trans;
			}
		}
	}
}