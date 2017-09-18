#include "Fighter.h"
#include "Graphics\Texture.h"
#include "Components/SpriteTileSheet.h"

Fighter::Fighter(sfloat startPositionX, sfloat startPositionY, Blz::Graphics::Texture texture) 
{
	position.Add(startPositionX, startPositionY);
	spriteSheet.SetTexture(texture);
	this->originalPosition.x = startPositionX;
	this->originalPosition.y = startPositionY;
}
