#pragma once
#include "Vector3D.h"
#include "Containers\Array.h"

namespace Blz
{
	namespace Graphics
	{
		namespace GL
		{
			auto InitializeGLBuffer(Blz::Array<Vector3D, 6> vertexData) -> void;
		}
	}
}