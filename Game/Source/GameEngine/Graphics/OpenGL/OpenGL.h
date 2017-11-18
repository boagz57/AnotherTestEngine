#pragma once
#include "Vertex2D.h"
#include "Containers\Array.h"

namespace Blz
{
	namespace Graphics
	{
		namespace GL
		{
			auto InitializeGPUBuffer(Blz::Array<Vertex2D, 6> vertexData) -> GLuint;
			auto DrawTexture(Blz::Array <Vertex2D, 6> vertexData, GLuint textureID, GLuint VBOID) -> void;
		}
	}
}