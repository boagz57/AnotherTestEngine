#pragma once
#include "Scene.h"

class Game
{
public:
	Game();
	~Game();

	virtual void GameLogic(Scene& scene) = 0;
};

