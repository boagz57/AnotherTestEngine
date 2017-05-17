#pragma once
#include "GLTexture.h"
#include "TextureCache.h"

namespace Blz
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		Blz::OpenGL::GLTexture GetTexture(Blz::string texturePath);

	private:
		static TextureCache textureCache;
	};
}
