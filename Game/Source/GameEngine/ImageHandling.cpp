#include <GL\glew.h>
#include "STB_Img\stb_image.h"
#include "ImageHandling.h"

namespace Blz
{
	namespace OpenGL 
	{
		GLTexture LoadImage(Blz::string filePath)
		{
			//Initiliazes struct members to 0
			GLTexture texture = {};

			int32 x, y, currentChannels;
			int32 forceChannels = 4;
			uchar8* imageData = 0;
			imageData = stbi_load(filePath.c_str(), &x, &y, &currentChannels, forceChannels);

			if (imageData == nullptr)
			{
				LOG("ERROR: Could not load image file!");
			};

			texture.width = x;
			texture.height = y;

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

			//Send down imageData to openGL and set some parameters for image
			glGenTextures(1, &(texture.id));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//Check if image is a power of 2 (which makes image compatible with older versions of opengl, also make things easier 
			//for openGL to work with). If check is done with bitwise operations to keep check as fast as possible
			if ((texture.width & (texture.width - 1)) != 0 || (texture.height & (texture.height - 1)) != 0)
			{
				LOG("WARNING: %s texture is not a power of 2 dimensions\n\n", filePath.c_str());
			};

			//Unbind Texture
			glBindTexture(GL_TEXTURE_2D, 0);

			return texture;
		}
	}
}