#include <GL\glew.h>
#include "Vector3D.h"
#include "OpenGL.h"

namespace Blz
{
	namespace Graphics
	{
		namespace GL 
		{
			auto InitializeGPUBuffer(Blz::Array<Vector3D, 6> vertexData) -> GLuint
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * vertexData.size()), &vertexData.front(), GL_DYNAMIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				return vboID;
			}

			auto DrawTexture(Blz::Array<Vector3D, 6> vertexData, GLuint textureID, GLuint VBOID) -> void
			{
				BGZ_RUNTIME_ASSERT(textureID != 0, "Texture id is invalid!");
				BGZ_RUNTIME_ASSERT(VBOID != 0, "VBO id is invalid!");

				glBindTexture(GL_TEXTURE_2D, textureID);

				glBindBuffer(GL_ARRAY_BUFFER, VBOID);

				//Send down new text coords to draw
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * vertexData.size()), &vertexData.front(), GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glDrawArrays(GL_TRIANGLES, 0, vertexData.size());

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}