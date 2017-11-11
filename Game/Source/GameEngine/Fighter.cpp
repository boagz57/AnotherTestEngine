#include "Fighter.h"
#include "Graphics\Texture.h"

void Fighter::Init(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture)
{
	RUNTIME_ASSERT((uint16)startingWorldPositionX <= c_windowWidth && (uint16)startingWorldPositionY <= c_windowHeight, "Trying to start fighter's position outside screen bounds!");
	RUNTIME_ASSERT((uint16)startingWorldPositionX >= 0 && (uint16)startingWorldPositionY >= 0, "Trying to start fighter's position outside screen bounds!");

	position.Add(startingWorldPositionX, startingWorldPositionY);
	spriteSheet.Init(texture, glm::ivec2{ 10, 4 }, 3);

	this->originalPosition.x = startingWorldPositionX;
	this->originalPosition.y = startingWorldPositionY;
}
