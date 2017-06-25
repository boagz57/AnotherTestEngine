#pragma once
#include "Graphics\GLTexture.h"

namespace Blz
{
	//Load image into GPU and return a handle to the texture
	Blz::Graphics::GLTexture LoadImageToGPU(Blz::string& filePath);
}