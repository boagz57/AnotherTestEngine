#include "Fighter.h"
#include "ErrorContext.h"
#include "Graphics/Sprite.h"

Fighter::Fighter(Blz::string imageFilePath, uint16 startPositionX, uint16 startPositionY)
{
	Blz::Err::ErrorContext ec("When initializing fighter character with image", imageFilePath);

	sprite.Init(startPositionX, startPositionY, 200, 200, imageFilePath);
}

Fighter::~Fighter()
{
}