#pragma once
#include "Containers/Map.h"
#include "BlueGod.h"
#include "Fighter.h"

class Game
{
public:
	Game() = default;

	void Init();
	void Update();
	void Shutdown();

	void MoveRight(Fighter* const fighter);
	void MoveLeft(Fighter* const fighter);
	void Jump(Fighter* const fighter);
	void Punch(Fighter* const fighter);

private:
	BlueGod player{};
	BlueGod enemy{};

	uint16 walkingRight = 0;
	uint16 punching = 0;
	uint16 idle = 0;

	uint16 AIWalkingRight = 0;
	uint16 AIIdle = 0;

};

