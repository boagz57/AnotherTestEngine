#include "Game.h"
#include "GameEngine/Animation/AnimationManager.h"

extern Blz::Animation::AnimationManager animation;

void Game::Init(Fighter* fighter)
{
	uint16 walkingUp = animation.CreateAnimation(8, 7);
	animationMap[AnimationState::WALKINGUP] = walkingUp;
}

void Game::Update(Fighter* fighter)
{
	animation.PlayAnimation(animationMap[AnimationState::WALKINGUP]);
}

void Game::Shutdown()
{

}
