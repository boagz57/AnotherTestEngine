#pragma once
#include "../Texture.h"
#include "Components\Transform.h"
#include "Components\Sprite.h"

namespace Blz
{
	namespace Graphics 
	{
		namespace System
		{
			TransformComponent ConvertWorldUnitsToScreenPixels(TransformComponent fighterTransformToConvert, uint16 const windowWidth);
			SpriteComponent SetSpriteScreenLocation(TransformComponent fighterTransform, SpriteComponent fighterSprite, Texture textureToSet);
		}
	}
}