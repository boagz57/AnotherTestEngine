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

			auto GetID() const -> GLuint { ERRASSERT(id != 0, "Texture not created properly!"); return id; };
			auto GetWidth() const -> uint16 { return static_cast<uint16>(width); };
			auto GetHeight() const -> uint16 { return static_cast<uint16>(height); };

		private:
			GLuint id{0};
			int32 width = 0;
			int32 height = 0;
			int32 channels = 0;
		};
	}
}