#include "Components/Position.h"
#include "SystemHelpers\SystemHelpers.h"
#include "../Window.h"
#include "GraphicsSystems.h"

namespace Blz
{
	namespace Graphics
	{
		namespace CompSystem
		{
			Comp::Position ConvertWorldUnitsToScreenPixels(Comp::Position fighterTransformToConvert, uint16 const windowWidth)
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

			Comp::SpriteTileSheet SetSpriteScreenLocation(Comp::Position fighterTransform, Comp::SpriteTileSheet fighterSprite)
			{
				fighterSprite.SetScreenTargetLocationAndTileDimensions(fighterTransform.GetCurrentPosition().x, fighterTransform.GetCurrentPosition().y, glm::ivec2{ 8, 4 });
				
				SysHelper::SendFighterSpriteDataToGPU(fighterSprite);

				return fighterSprite;
			}
		}
	}
}