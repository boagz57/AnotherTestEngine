#include <GL/glew.h>
#include <GLM\detail\type_vec3.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include "GLLogging.h"
#include "../Fighter.h"
#include "ShaderProgram.h"
#include "../Vector3D.h"
#include "Sprite.h"
#include "Renderer.h"

namespace Blz
{
	namespace Graphics
	{
		Renderer::Renderer() 
		{
		}

		Renderer::~Renderer()
		{}

		void Renderer::Init()
		{
			shaderProgram.Init("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");
			this->shaderProgram.Compile();
			this->shaderProgram.AddAttribute("vertexPosition");
			this->shaderProgram.AddAttribute("textCoord");
			this->shaderProgram.Link();
			this->shaderProgram.Bind();

			//This function should only be run in debug or development builds as it can be very computationally
			//expensive 
			Blz::Graphics::IsProgramValid(this->shaderProgram.programID);
			Blz::Graphics::LogShaderProgramProperties(this->shaderProgram.programID);

			GLuint uniformLocation = this->shaderProgram.GetUniformLocation("basicTexture");
			glUniform1i(uniformLocation, 0);
		}

		void Renderer::Draw(Scene& scene)
		{
			glm::mat4 orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(1024), 0.0f, static_cast<sfloat>(768));
			GLuint transformationMatrixUniformLocation = this->shaderProgram.GetUniformLocation("transformationMatrix");

			glm::vec3 newFighterPosition;

			for (uint16 i = 0; i < scene.fighters.size(); ++i)
			{
				newFighterPosition = scene.fighters.at(i).position;
				glm::mat4 transformationMatrix = glm::translate(orthoProjection, newFighterPosition);
				glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));

				glBindTexture(GL_TEXTURE_2D, scene.fighters.at(i).sprite.texture.id);
				glBindBuffer(GL_ARRAY_BUFFER, scene.fighters.at(i).sprite.vboID);

				glDrawArrays(GL_TRIANGLES, 0, 6);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			};
		}
	}
}