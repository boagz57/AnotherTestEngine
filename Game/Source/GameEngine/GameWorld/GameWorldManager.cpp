#include "GameWorldManager.h"
#include "Components\Position.h"
#include "Systems\GameWorldSystems.h"

namespace Blz
{
	namespace GameWorld
	{
		void GameWorldManager::Init(Scene& scene)
		{
			Blz::Graphics::Texture fighterTexture("Girl.png");
			ERRASSERT(fighterTexture.ID() != 0, "Texture did not load properly!");

			for (uint16 i = 0; i < scene.fighters.size(); ++i)
			{
				SpriteTileSheetComponent newSprite = System::SetSpriteWidthAndHeight(scene.fighters.at(i).GetComponent<SpriteTileSheetComponent>(), 200.0f, 200.0f);
				SpriteTileSheetComponent newSprite2 = System::SetSpriteTexture(newSprite, fighterTexture);

				scene.fighters.at(i).Insert(newSprite2);
			}
		}

		void GameWorldManager::Update(Scene& scene)
		{
		}
	}
}