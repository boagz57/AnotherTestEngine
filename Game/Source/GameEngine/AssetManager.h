#pragma once
#include "Graphics\Texture.h"
#include "TextureCache.h"

namespace Blz
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		Blz::Graphics::Texture GetTexture(Blz::string texturePath);

	private:
		static TextureCache textureCache;
	};
}
