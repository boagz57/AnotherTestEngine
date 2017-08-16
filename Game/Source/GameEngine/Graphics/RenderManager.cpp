#include <GL\glew.h>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "ShaderProgram.h"
#include "../Components/Sprite.h"
#include "Texture.h"
#include "../Vector3D.h"
#include "RenderManager.h"
#include "../Scene.h"
#include "../Fighter.h"

namespace Blz
{
	namespace Graphics
	{
		RenderManager::RenderManager()
		{}

		RenderManager::~RenderManager()
		{}

		void RenderManager::Init(Scene& scene, Window& window)
		{
			for (Fighter& fighter : scene.fighters)
			{
				sfloat fighterPosX = fighter.GetComponent<TransformComponent>().GetCurrentPosition().x;
				sfloat fighterPosY = fighter.GetComponent<TransformComponent>().GetCurrentPosition().y;

				//Convert my theoretical world units to actual screen pixels by deciphering if window is 1080p or 720p
				//and doing necessary math for conversion. My logical screen grid contains 160 'world units' in the x and 90 in 
				//the y and this 160x90 unit subdivision is a common factor of both 720p and 1080p screens. This way I will get a whole 
				//number of pixels per unit in both cases which is important to avoid fractional scales that can distort artwork.
				if (window.width == 1920)
				{
					fighterPosX *= 12;
					fighterPosY *= 12;
				}
				else if (window.width == 1280)
				{
					fighterPosX *= 8;
					fighterPosY *= 8;
				}

				//TODO: Make into a system
				SpriteComponent newSprite = fighter.GetComponent<SpriteComponent>();
				newSprite.SetScreenTargetLocation(fighterPosX, fighterPosY);
				fighter.Insert(newSprite);
			}

			//Turn OpenGL normalized device coodinates (-1 to 1) to pixel coordinates
			orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(window.width), 0.0f, static_cast<sfloat>(window.height));

			for (Fighter& fighter : scene.fighters)
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighter.GetComponent<SpriteComponent>().GetVertexData().size()), &fighter.GetComponent<SpriteComponent>().GetVertexData().front(), GL_DYNAMIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);
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

				glm::vec2 translationAmount = fighter.GetComponent<TransformComponent>().GetCurrentPosition() - fighter.originalPosition;
				glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ translationAmount.x, translationAmount.y, 0.0f });
				glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));

				glBindTexture(GL_TEXTURE_2D, fighter.GetComponent<SpriteComponent>().GetTexture().id);
				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}