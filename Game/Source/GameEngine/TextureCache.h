#pragma once
#include "GLTexture.h"
#include "../Universal/Map.h"

namespace Blz
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Blz::OpenGL::GLTexture GetTexture(const Blz::string textureFilePath);

	private:
		Blz::Map<Blz::string, Blz::OpenGL::GLTexture> textureMap;
	};
}