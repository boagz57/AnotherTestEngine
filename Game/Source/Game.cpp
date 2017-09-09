#include "Game.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Velocity.h"
#include "GameEngine/Animation/AnimationManager.h"
#include "GameEngine/Input/InputManager.h"
#include "GameEngine/Physics/PhysicsManager.h"

extern Blz::Animation::AnimationManager animation;
extern Blz::Input::InputManager Input;
extern Blz::Physics::PhysicsManager Physics;
extern Scene scene;

void Game::Init()
{
	uint16 walkingUp = animation.CreateAnimation(8, 7);
	animationMap[AnimationState::WALKINGUP] = walkingUp;

	Blz::Graphics::Texture fighterTexture("Girl.png");

	p_Player = scene.CreateFighter(160.0f, 0.0f, fighterTexture);
	p_AI = scene.CreateFighter(80.0f, 45.0f, fighterTexture);

	Input.SetFighterToBeControllable(p_Player);
}

void Game::Update()
{
	Physics.Move(p_Player, -0.1f, 0.1f);
	animation.PlayAnimation(animationMap[AnimationState::WALKINGUP]);
}

void Game::Shutdown()
{

}
