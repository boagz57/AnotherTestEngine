#include <GL\glew.h>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "../ErrorHandling.h"
#include "ShaderProgram.h"
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

		void RenderManager::Init(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				sfloat fighterPosX = fighter.position.GetCurrentState().x;
				sfloat fighterPosY = fighter.position.GetCurrentState().y;

				fighter.sprite.SetTargetPosition(fighterPosX, fighterPosY);
			}

			for (Fighter& fighter : scene.fighters)
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighter.sprite.GetVertexData().size()), &fighter.sprite.GetVertexData().front(), GL_DYNAMIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}

		void RenderManager::Update(Scene& scene, ShaderProgram& shader)
		{
			glm::mat4 orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(1024), 0.0f, static_cast<sfloat>(768));
			GLuint transformationMatrixUniformLocation = shader.GetUniformLocation("transformationMatrix");

			GLuint uniformLocation = shader.GetUniformLocation("basicTexture");
			glUniform1i(uniformLocation, 0);

			GLuint vboID = 0;

			for (Fighter& fighter : scene.fighters)
			{
				++vboID;

				glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{ fighter.transform.GetCurrentTranslationAmount().x, fighter.transform.GetCurrentTranslationAmount().y, 0.0f });
				glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));

				glBindTexture(GL_TEXTURE_2D, fighter.sprite.GetTexture().id);
				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				fighter.transform.ResetTranslation();
			}
		}
	}
}