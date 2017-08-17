#include "GameWorldManager.h"
#include "../Components/Transform.h"
#include "Systems\GameWorldSystems.h"

namespace Blz
{
	namespace GameWorld
	{
		GameWorldManager::GameWorldManager()
		{
		}


		GameWorldManager::~GameWorldManager()
		{
		}

		void GameWorldManager::Init(Scene& scene)
		{
			for (uint16 i = 0; i < scene.fighters.size(); ++i)
			{
				TransformComponent startingFighterPosition = System::SetFighterStartingPosition(scene.fighters.at(i).GetComponent<TransformComponent>(), scene.fighterStartingPositions.at(i));
				SpriteComponent newSprite = System::SetSpriteWidthAndHeight(scene.fighters.at(i).GetComponent<SpriteComponent>(), 200.0f, 200.0f);

				scene.fighters.at(i).Insert(newSprite);
				scene.fighters.at(i).Insert(startingFighterPosition);
			}
		}

		void GameWorldManager::Update(Scene& scene)
		{
		}
	}
}