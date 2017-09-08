#include "Fighter.h"
#include "Graphics\Texture.h"
#include "Components/SpriteTileSheet.h"

Fighter::Fighter(sfloat startPositionX, sfloat startPositionY, Blz::Graphics::Texture texture) 
{
	ComponentHolder<Comp::Position>::component.SetPosition(startPositionX, startPositionY);
	ComponentHolder<Comp::SpriteTileSheet>::component.SetTexture(texture);
}
