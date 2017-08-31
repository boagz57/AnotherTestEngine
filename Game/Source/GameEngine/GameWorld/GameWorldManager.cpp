#include "GameWorldManager.h"
#include "Components\Position.h"
#include "Systems\GameWorldSystems.h"

namespace Blz
{
	namespace GameWorld
	{
		void GameWorldManager::Init(Scene& scene)
		{
			for (uint16 i = 0; i < scene.fighters.size(); ++i)
			{
				PositionComponent startingFighterPosition = System::SetFighterStartingPosition(scene.fighters.at(i).GetComponent<PositionComponent>(), scene.fighterStartingPositions.at(i));
				SpriteTileSheetComponent newSprite = System::SetSpriteWidthAndHeight(scene.fighters.at(i).GetComponent<SpriteTileSheetComponent>(), 200.0f, 200.0f);

				scene.fighters.at(i).Insert(newSprite);
				scene.fighters.at(i).Insert(startingFighterPosition);
			}
		}

		void GameWorldManager::Update(Scene& scene)
		{
		}
	}
}