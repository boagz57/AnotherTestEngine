#pragma once
#include "Graphics\Texture.h"
#include "../Universal/Map.h"

namespace Blz
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Blz::Graphics::Texture GetTexture(Blz::string textureFilePath);

	private:
		Blz::Map<Blz::string, Blz::Graphics::Texture> textureMap;
	};
}