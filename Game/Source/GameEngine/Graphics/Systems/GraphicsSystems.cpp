#include "GraphicsSystems.h"
#include "Components/Position.h"
#include "../Window.h"

namespace Blz
{
	namespace Graphics
	{
		namespace System
		{
			PositionComponent ConvertWorldUnitsToScreenPixels(PositionComponent fighterTransformToConvert, uint16 const windowWidth)
			{
				if (windowWidth == 1920)
				{
					fighterTransformToConvert.MultiplyPositionBy(12, 12);
				}
				else if (windowWidth == 1280)
				{
					fighterTransformToConvert.MultiplyPositionBy(8, 8);
				}

				return fighterTransformToConvert;
			}

			SpriteTileSheetComponent SetSpriteScreenLocation(PositionComponent fighterTransform, SpriteTileSheetComponent fighterSprite, Texture textureToSet)
			{
				fighterSprite.SetScreenTargetLocationAndTileDimensions(fighterTransform.GetCurrentPosition().x, fighterTransform.GetCurrentPosition().y, glm::ivec2{ 8, 4 });
				fighterSprite.SetTextureID(textureToSet.ID());
				return fighterSprite;
			}
		}
	}
}