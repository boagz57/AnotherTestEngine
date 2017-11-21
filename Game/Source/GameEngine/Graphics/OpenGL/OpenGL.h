#pragma once
#include "Vertex2D.h"
#include "Containers\Array.h"

namespace Blz
{
	namespace Graphics
	{
		namespace GL
		{
			//Returns a vertex buffer ID
			template<const int numberOfVertices>
			auto InitializeGPUBuffer(Blz::Array<Vertex2D, numberOfVertices> vertexData) -> GLuint;
			auto DrawTexture(Blz::Array <Vertex2D, 6> vertexData, GLuint textureID, GLuint VBOID) -> void;

			template<const int numberOfVertices>
			auto InitializeGPUBuffer(Blz::Array<Vertex2D, numberOfVertices> vertexData) -> GLuint
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex2D) * vertexData.size()), &vertexData.front(), GL_DYNAMIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				return vboID;
			}
		}
	}
}