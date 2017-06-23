#include <GL\glew.h>
#include <STB_Img\stb_image.h>
#include "Graphics\GLImageHandling.h"
#include "ErrorHandling.h"
#include "ImageHandling.h"

namespace Blz
{
	namespace Graphics 
	{
		GLTexture LoadImageToGPU(Blz::string& filePath)
		{
			Blz::Err::ErrorContext ec("When loading image from file", filePath);

			//Initiliazes struct members to 0
			GLTexture texture = {};

			int32 imgWidth = 0, imgHeight = 0, currentChannels;
			int32 forceChannels = 4;
			uchar8* imageData = 0;
			imageData = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &currentChannels, forceChannels);
			RUNTIME_ASSERT(imgWidth >= 0, "Image width <= 0!");
			RUNTIME_ASSERT(imgHeight >= 0, "Image height <= 0!");

			ERRASSERT(imageData, "Image data invalid!");

			texture.width = imgWidth;
			texture.height = imgHeight;

			//Check if image is a power of 2 (which makes image compatible with older versions of opengl, also make things easier 
			//for openGL to work with). If check is done with bitwise operations to keep check as fast as possible
			RUNTIME_ASSERT((texture.width & (texture.width - 1)) == 0 || (texture.height & (texture.height - 1)) == 0, "Image dimensions are not a power of 2!");

			//Flip image right side up before sending to OpenGL since openGL will read it in upside down. Following code is utilizing pointer
			//arithmetic 
			int32 widthInBytes = texture.width * 4;
			uchar8 *p_topRowOfTexels = nullptr;
			uchar8 *p_bottomRowOfTexels = nullptr;
			uchar8 temp = 0;
			int32 halfHeight = texture.height / 2;

			for (int32 row = 0; row < halfHeight; ++row)
			{
				p_topRowOfTexels = imageData + row * widthInBytes;
				p_bottomRowOfTexels = imageData + (texture.height - row - 1) * widthInBytes;

				for (int col = 0; col < widthInBytes; ++col)
				{
					temp = *p_topRowOfTexels;
					*p_topRowOfTexels = *p_bottomRowOfTexels;
					*p_bottomRowOfTexels = temp;
					p_topRowOfTexels++;
					p_bottomRowOfTexels++;
				}
			}

			SendImageDataToGPU(imageData, texture);

			return texture;
		}
	}
}