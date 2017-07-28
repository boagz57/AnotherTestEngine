#pragma once
#include "GameEngine/Game.h"
#include "GameEngine/Scene.h"

class ShadowGodsGame : public Game
{
public:
	ShadowGodsGame();
	~ShadowGodsGame();

	virtual void GameLogic(Scene& scene) override;
};

