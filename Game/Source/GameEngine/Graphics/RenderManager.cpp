#include <GL\glew.h>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <math.h>
#include <GLM\vec2.hpp>
#include "ShaderProgram.h"
#include "../Components/SpriteTileSheet.h"
#include "Texture.h"
#include "../Vector3D.h"
#include "RenderManager.h"
#include "Systems\GraphicsSystems.h"
#include "../Scene.h"
#include "../Fighter.h"

namespace Blz
{
	namespace Graphics
	{
		void RenderManager::Init(Scene& scene, Window& window)
		{
			//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
			orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(window.width), 0.0f, static_cast<sfloat>(window.height));

			for (Fighter& fighter : scene.fighters)
			{
				PositionComponent ConvertedPixelPosition = System::ConvertWorldUnitsToScreenPixels(fighter.GetComponent<PositionComponent>(), window.width);

				SpriteTileSheetComponent UpdatedSpriteLocation = System::SetSpriteScreenLocation(ConvertedPixelPosition, fighter.GetComponent<SpriteTileSheetComponent>());
				System::SendFighterSpriteDataToGPU(UpdatedSpriteLocation);

				fighter.Insert(UpdatedSpriteLocation);
			}
		}

		void RenderManager::Update(Scene& scene, ShaderProgram& shader)
		{
			GLuint transformationMatrixUniformLocation = shader.GetUniformLocation("transformationMatrix");

			GLuint uniformLocation = shader.GetUniformLocation("basicTexture");
			glUniform1i(uniformLocation, 0);

			GLuint vboID = 0;

			for (Fighter& fighter : scene.fighters)
			{
				++vboID;

				//Translate vertices of fighter to move him
				{
					glm::vec2 translationAmount = fighter.GetComponent<TransformComponent>().GetCurrentTranslation();

					//Round values to nearest int value to avoid fractional values which can create distorted art work
					translationAmount.x = rint(translationAmount.x);
					translationAmount.y = rint(translationAmount.y);

					glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ translationAmount.x, translationAmount.y, 0.0f });
					glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));
				}

				glBindTexture(GL_TEXTURE_2D, fighter.GetComponent<SpriteTileSheetComponent>().GetTextureID());

				//Send new 
				{
					glBindBuffer(GL_ARRAY_BUFFER, vboID);

					glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighter.GetComponent<SpriteTileSheetComponent>().GetVertexData().size()), &fighter.GetComponent<SpriteTileSheetComponent>().GetVertexData().front(), GL_DYNAMIC_DRAW);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));
				}

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//TODO: Remove zeroing out velocity from Renderer update. 
				VelocityComponent vel = fighter.GetComponent<VelocityComponent>();
				vel.ZeroOut();
				fighter.Insert(vel);
			}
		}
	}
}