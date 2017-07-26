#include "Fighter.h"
#include "ErrorContext.h"
#include "Graphics/Sprite.h"

Fighter::Fighter(Blz::string imageFilePath)
{
	Blz::Err::ErrorContext ec("When initializing fighter character with image", imageFilePath);

	sprite.Init(1024/2, 768/2, 200, 200, imageFilePath);
}

Fighter::~Fighter()
{
}

Sprite Fighter::GetSprite()
{
	return sprite;
}