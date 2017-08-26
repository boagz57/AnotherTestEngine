#include "GraphicsSystems.h"
#include "../Window.h"

namespace Blz
{
	namespace Graphics
	{
		namespace System
		{
			TransformComponent ConvertWorldUnitsToScreenPixels(TransformComponent fighterTransform, uint16 const windowWidth)
			{
				if (windowWidth == 1920)
				{
					fighterTransform.MultiplyPosition(12, 12);
				}
				else if (windowWidth == 1280)
				{
					fighterTransform.MultiplyPosition(8, 8);
				}

				return fighterTransform;
			}

			SpriteComponent SetSpriteScreenLocation(TransformComponent fighterTransform, SpriteComponent fighterSprite, Texture texture)
			{
				fighterSprite.SetScreenTargetLocation(fighterTransform.GetCurrentPosition().x, fighterTransform.GetCurrentPosition().y);
				fighterSprite.SetTextureID(texture.ID());
				return fighterSprite;
			}
		}
	}
}