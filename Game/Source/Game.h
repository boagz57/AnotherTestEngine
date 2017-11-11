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

	uint16 walkingRight{};
	uint16 punching{};
	uint16 idle{};

	uint16 AIWalkingRight{};
	uint16 AIIdle{};

};

