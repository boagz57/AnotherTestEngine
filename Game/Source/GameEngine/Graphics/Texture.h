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

			GLuint ID() { return id; };

		private:
			GLuint id = 0;
			int32 width = 0;
			int32 height = 0;
			int32 channels = 0;
		};
	}
}