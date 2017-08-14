#include <STB_Img\stb_image.h>
#include "Texture.h"

namespace Blz
{
	namespace Graphics
	{
		Texture::Texture()
		{}

		Texture::Texture(const Blz::string c_imageFilePath)
		{
			Blz::Err::ErrorContext ec("When constructing texture from", c_imageFilePath);

			int32 forceChannels = 4;
			unsigned char* imageData = stbi_load(c_imageFilePath.c_str(), &this->width, &this->height, &channels, forceChannels);

			RUNTIME_ASSERT(this->width >= 0, "Image width <= 0!");
			RUNTIME_ASSERT(this->height >= 0, "Image height <= 0!");

			ERRASSERT(imageData != nullptr, "Image data {} did not load properly!", c_imageFilePath);

			//Check if image is a power of 2 (which makes image compatible with older versions of opengl, also make things easier 
			//for openGL to work with). If check is done with bitwise operations to keep check as fast as possible
			RUNTIME_ASSERT((this->width & (this->width - 1)) == 0 || (this->height & (this->height - 1)) == 0, "Image dimensions are not a power of 2!");

			//Flip image right side up before sending to OpenGL since openGL will read it in upside down. Following code is utilizing pointer
			//arithmetic 
			int32 widthInBytes = this->width * 4;
			unsigned char* p_topRowOfTexels = nullptr;
			unsigned char* p_bottomRowOfTexels = nullptr;
			unsigned char temp = 0;
			int32 halfHeight = this->height / 2;

			for (int32 row = 0; row < halfHeight; ++row)
			{
				p_topRowOfTexels = imageData + row * widthInBytes;
				p_bottomRowOfTexels = imageData + (this->height - row - 1) * widthInBytes;

				for (int col = 0; col < widthInBytes; ++col)
				{
					temp = *p_topRowOfTexels;
					*p_topRowOfTexels = *p_bottomRowOfTexels;
					*p_bottomRowOfTexels = temp;
					p_topRowOfTexels++;
					p_bottomRowOfTexels++;
				}
			}

			//Send down imageData to openGL and set some default parameters for image
			glGenTextures(1, &(this->id));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//Unbind Texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture::~Texture()
		{}
	}
}