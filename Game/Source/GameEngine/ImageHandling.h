#pragma once
#include "Graphics\GLTexture.h"

namespace Blz
{
	namespace Graphics 
	{
		//Load image into GPU and return a handle to the texture
		GLTexture LoadImageToGPU(Blz::string& filePath);
	}
}