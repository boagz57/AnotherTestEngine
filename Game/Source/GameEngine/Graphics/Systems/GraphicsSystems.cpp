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
				ec.AddContext("When converting my world units to screen pixels");

				if (windowWidth == 1920)
				{
					fighterTransformToConvert.MultiplyBy(12, 12);
				}
				else if (windowWidth == 1280)
				{
					fighterTransformToConvert.MultiplyBy(8, 8);
				}

				return fighterTransformToConvert;
			}

			Comp::SpriteTileSheet SetSpriteScreenLocation(Comp::Position fighterTransform, Comp::SpriteTileSheet fighterSprite)
			{
				ec.AddContext("When setting sprite screen location");

				fighterSprite.SetScreenTargetLocationAndTileDimensions(fighterTransform.GetCurrentPosition().x, fighterTransform.GetCurrentPosition().y, glm::ivec2{ 8, 4 });
				
				SysHelper::InitializeGLBuffer(fighterSprite.GetVertexData());

				return fighterSprite;
			}
		}
	}
}