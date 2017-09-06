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

	void Init(Fighter* fighter);
	void Update(Fighter* fighter);
	void Shutdown();

private:
	Blz::Map<AnimationState, uint16> animationMap;
};

