#pragma once
#include "GLTexture.h"

namespace Blz
{
	namespace Graphics
	{
		void SendImageDataToGPU(uchar8* imageData, GLTexture& texture);
	}
}
