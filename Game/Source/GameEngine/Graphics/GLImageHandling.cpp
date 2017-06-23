#include "GLImageHandling.h"

namespace Blz
{
	namespace Graphics
	{
		void SendImageDataToGPU(uchar8* imageData, GLTexture& texture)
		{
			//Send down imageData to openGL and set some parameters for image
			glGenTextures(1, &(texture.id));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//Unbind Texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}