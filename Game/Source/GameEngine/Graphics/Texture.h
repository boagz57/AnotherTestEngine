#pragma once
#include <GL\glew.h>

namespace Blz
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture() = default;
			explicit Texture(const Blz::string imageFilePath);
			~Texture() = default;

			GLuint const ID() const { return id; };

		private:
			GLuint id = 0;
			int32 width = 0;
			int32 height = 0;
			int32 channels = 0;
		};
	}
}