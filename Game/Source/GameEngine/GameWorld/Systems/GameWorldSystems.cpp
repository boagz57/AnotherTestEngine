#include "Fighter.h"
#include "Components\SpriteTileSheet.h"
#include "Components\Transform.h"
#include "GameWorldSystems.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace CompSystem
		{
			Comp::SpriteTileSheet SetSpriteTexture(Comp::SpriteTileSheet fighterSprite, Blz::Graphics::Texture texture)
			{
				fighterSprite.SetTextureID(texture.ID());
				return fighterSprite;
			}

			Comp::Sprite SetSpriteTexture(Comp::Sprite fighterSprite, Blz::Graphics::Texture texture)
			{
				fighterSprite.SetTextureID(texture.ID());
				return fighterSprite;
			}

			Comp::SpriteTileSheet SetSpriteWidthAndHeight(Comp::SpriteTileSheet fighterSprite, sfloat const spriteWidth, sfloat const spriteHeight)
			{
				fighterSprite.SetWidthAndHeight(spriteWidth, spriteHeight);
				return fighterSprite;
			}
		}
	}
}