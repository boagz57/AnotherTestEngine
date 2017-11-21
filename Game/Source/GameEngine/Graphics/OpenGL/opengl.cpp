#include <GL\glew.h>
#include "Vertex2D.h"
#include "OpenGL.h"

namespace Blz
{
	namespace Graphics
	{
		namespace GL 
		{
			auto DrawTexture(Blz::Array<Vertex2D, 6> vertexData, GLuint textureID, GLuint VBOID) -> void
			{
				BLZ_RUNTIME_ASSERT(textureID != 0, "Texture id is invalid!");
				BLZ_RUNTIME_ASSERT(VBOID != 0, "VBO id is invalid!");

				glBindTexture(GL_TEXTURE_2D, textureID);

				glBindBuffer(GL_ARRAY_BUFFER, VBOID);

				//Send down new text coords to draw
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex2D) * vertexData.size()), &vertexData.front(), GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, textureCoordinates));

				glDrawArrays(GL_TRIANGLES, 0, vertexData.size());

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}