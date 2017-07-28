#include "ShadowGodsGame.h"
#include "GameEngine/Fighter.h"
#include "GameEngine/Scene.h"

ShadowGodsGame::ShadowGodsGame()
{
}

ShadowGodsGame::~ShadowGodsGame()
{
}

void ShadowGodsGame::GameLogic(Scene& scene)
{
	scene.fighters.at(0);

	if (scene.fighters.at(0).GetPosition().x > 0)
	{
		LOG("Helllllllo");
	}
}
