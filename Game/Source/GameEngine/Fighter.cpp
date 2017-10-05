#include "Fighter.h"
#include "Graphics\Texture.h"

void Fighter::Init(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture)
{
	RUNTIME_ASSERT(startingWorldPositionX <= 160.0f && startingWorldPositionY <= 90.0f, "Trying to start fighter's position outside world bounds!");
	RUNTIME_ASSERT(startingWorldPositionX >= 0.0f && startingWorldPositionY >= 0.0f, "Trying to start fighter's position outside world bounds!");

	position.Add(startingWorldPositionX, startingWorldPositionY);
	spriteSheet.Init(texture, glm::ivec2{ 10, 4 }, 3);

	this->originalPosition.x = startingWorldPositionX;
	this->originalPosition.y = startingWorldPositionY;
}
