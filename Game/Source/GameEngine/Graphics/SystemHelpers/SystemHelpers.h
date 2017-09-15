#pragma once
#include "Components\Sprite.h"
#include "Containers\Array.h"
#include "Components\SpriteTileSheet.h"

namespace Blz
{
	namespace Graphics
	{
		namespace SysHelper
		{
			void InitializeGLBuffer(Blz::Array<Vector3D, 6> vertexData);
		}
	}
}