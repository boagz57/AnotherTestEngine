#pragma once
#include "Graphics\GLTexture.h"
#include "../Universal/Map.h"

namespace Blz
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Blz::Graphics::GLTexture GetTexture(Blz::string textureFilePath);

	private:
		Blz::Map<Blz::string, Blz::Graphics::GLTexture> textureMap;
	};
}