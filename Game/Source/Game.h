#pragma once
#include "GameEngine/Input/InputManager.h"
#include "GameEngine/Physics/PhysicsManager.h"
#include "GameEngine/Animation/AnimationManager.h"
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
	Blz::Input::Manager input;
	Blz::Physics::Manager physics;
	Blz::Animation::Manager animation;

	Fighter* p_Player;
	Fighter* p_AI;

	Blz::Map<AnimationState, uint16> animationMap;
};

