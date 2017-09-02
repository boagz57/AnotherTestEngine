#include "GraphicsSystems.h"
#include "Components/Position.h"
#include "../Window.h"

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
				return fighterSprite;
			}

			void SendFighterSpriteDataToGPU(Comp::SpriteTileSheet fighterSprite)
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighterSprite.GetVertexData().size()), &fighterSprite.GetVertexData().front(), GL_DYNAMIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void SendFighterSpriteDataToGPU(Comp::Sprite fighterSprite)
			{
				GLuint vboID = 0;
				glGenBuffers(1, &vboID);

				glBindBuffer(GL_ARRAY_BUFFER, vboID);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * fighterSprite.GetVertexData().size()), &fighterSprite.GetVertexData().front(), GL_DYNAMIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	}
}