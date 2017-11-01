#include <STB_Img\stb_image.h>
#include <string>
#include "Texture.h"

namespace Blz
{
	namespace Graphics
	{
		Texture::Texture(const std::string c_imageFilePath)
		{
			int32 forceChannels = 4;							   
			auto* p_ImageData = stbi_load(c_imageFilePath.c_str(), &this->width, &this->height, &channels, forceChannels);

			RUNTIME_ASSERT(this->width >= 0, "Image width not specified!");
			RUNTIME_ASSERT(this->height >= 0, "Image height not specified!");

			RUNTIME_ASSERT(p_ImageData != nullptr, "Image data {} did not load properly!");

			//TODO: uncomment RUNTIMEASSERT below so I check if images loaded are dimensions of 2
			//Check if image is a power of 2 (which makes image compatible with older versions of opengl, also make things easier 
			//for openGL to work with). If check is done with bitwise operations to keep check as fast as possible
			//RUNTIME_ASSERT((this->width & (this->width - 1)) == 0 || (this->height & (this->height - 1)) == 0, "Image dimensions are not a power of 2!");
						
			{//Send down imageData to openGL and set some default parameters for image
				glGenTextures(1, &(this->id));

				RUNTIME_ASSERT(this->id != 0, "Texture was not properly generated!");

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, this->id);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_ImageData);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				//Enable alpha channel for transparency
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//Unbind Texture
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}
}