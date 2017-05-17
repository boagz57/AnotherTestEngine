#include "GLTexture.h"
#include "ImageHandling.h"
#include "TextureCache.h"

namespace Blz
{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	Blz::OpenGL::GLTexture TextureCache::GetTexture(const Blz::string textureFilePath)
	{
		using namespace Blz::OpenGL;

		//Search texture map to see if image is already cached
		auto it = this->textureMap.find(textureFilePath);

		//If texture is not already found in map then load it into map
		if (it == textureMap.end())
		{
			//Load Texture to OpenGL
			GLTexture newTexture = Blz::OpenGL::LoadImage(textureFilePath);
			textureMap.emplace(std::make_pair(textureFilePath, newTexture));

			return newTexture;
		}

		return it->second;
	}
}