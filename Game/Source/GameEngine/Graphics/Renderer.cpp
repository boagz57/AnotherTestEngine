#include <GL/glew.h>
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

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textCoordinate));

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}