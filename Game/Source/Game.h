#pragma once
#include "Containers/Map.h"
#include "Fighter.h"

enum class AnimationState
{
	WALKINGUP
};

class Game
{
public:
	Game() = default;

	void Init();
	void Update();
	void Shutdown();

private:
	Fighter* p_Player;
	Fighter* p_AI;
	Blz::Map<AnimationState, uint16> animationMap;
};

