#pragma once
#include "Graphics\GLTexture.h"
#include "TextureCache.h"

namespace Blz
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		Blz::Graphics::GLTexture GetTexture(Blz::string texturePath);

	private:
		static TextureCache textureCache;
	};
}
