#include <GL\glew.h>
#include "Vector3D.h"
#include "OpenGL.h"

namespace Blz
{
	namespace Graphics
	{
		namespace GL 
		{
			auto InitializeGLBuffer(Blz::Array<Vector3D, 6> vertexData) -> void
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * vertexData.size()), &vertexData.front(), GL_DYNAMIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}