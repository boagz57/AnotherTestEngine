#pragma once
#include <GL\glew.h>

namespace Blz
{
	namespace Graphics
	{
		struct GLTexture
		{
			GLuint id = 0;
			int32 width = 0;
			int32 height = 0;
		};
	}
}