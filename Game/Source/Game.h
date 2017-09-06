#pragma once
#include "Fighter.h"

class Game
{
public:
	Game() = default;

	void Init(Fighter* fighter);
	void Update(Fighter* fighter);
	void Shutdown();

private:

};

