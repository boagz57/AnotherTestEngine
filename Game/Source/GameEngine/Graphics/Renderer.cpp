#include <GL/glew.h>
#include <GLM\detail\type_vec3.hpp>
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

		void Renderer::Init(Sprite& sprite)
		{
			this->sprite = sprite;
			glGenBuffers(1, &VBOID);

			glBindBuffer(GL_ARRAY_BUFFER, VBOID);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * sprite.vertexData.size()), &sprite.vertexData.front(), GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Renderer::Draw()
		{
			glBindTexture(GL_TEXTURE_2D, sprite.texture.id);
			glBindBuffer(GL_ARRAY_BUFFER, VBOID);

			//Position														  size 0 since position attribute is laid out first in Vector3D memory
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)0);
			//Texture Coordinates                                             text coords attribute is sizeof(glm::vec3) bytes into Vector3D since it's laid out after position attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)sizeof(glm::vec3));

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}