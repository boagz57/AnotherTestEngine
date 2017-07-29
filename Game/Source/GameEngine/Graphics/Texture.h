#pragma once
#include <GL\glew.h>

namespace Blz
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture();
			Texture(const Blz::string imageFilePath);
			~Texture();

			GLuint id = 0;

			//TODO: add a load texture function

		private:
			int32 width = 0;
			int32 height = 0;
			int32 channels = 0;
		};
	}
}