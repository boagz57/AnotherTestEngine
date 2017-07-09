#pragma once
#include <GL\glew.h>

namespace Blz
{
	namespace Graphics
	{
		class GLTexture
		{
		public:
			GLTexture();
			GLTexture(const Blz::string imageFilePath);
			~GLTexture();

			GLuint id = 0;

		private:
			int32 width = 0;
			int32 height = 0;
			int32 channels = 0;
		};
	}
}