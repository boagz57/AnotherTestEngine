#pragma once
#include <GL\glew.h>

namespace Blz::Graphics
{
	class Texture
	{
	public:
		Texture() = default;
		explicit Texture(const string imageFilePath);
		~Texture() = default;

		auto GetID() const -> GLuint { ERRASSERT(id != 0, "Texture not created properly!"); return id; };
		auto GetWidth() const -> uint16 { return static_cast<uint16>(width); };
		auto GetHeight() const -> uint16 { return static_cast<uint16>(height); };

	private:
		GLuint id{};
		int32 width{};
		int32 height{};
		int32 channels{};
	};
}