#include "Texture.h"
#include <spine\Atlas.h>
#include <spine\extension.h>

void _spAtlasPage_createTexture(spAtlasPage* page, const char* path)
{
	Blz::Graphics::Texture* p_texture = new Blz::Graphics::Texture(path);

	RUNTIME_ASSERT(p_texture != nullptr, "Atlas texture did no load properly!");

	page->rendererObject = p_texture;
	page->width = p_texture->GetWidth();
	page->height = p_texture->GetHeight();
}

void _spAtlasPage_disposeTexture(spAtlasPage* page)
{
	RUNTIME_ASSERT(page->rendererObject != nullptr, "Trying to delete invalid texture inside atlas!");

	delete page->rendererObject;
	page->rendererObject = nullptr;
}

char* _spUtil_readFile(const char* path, int* length)
{
	return _spReadFile(path, length);
}
