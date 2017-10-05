#include <SDL.h>
#include <functional>
#include "Game.h"
#include "GameEngine/Scene.h"
#include "GameEngine/AI/AIEngine.h"
#include "GameEngine/Input/InputEngine.h"
#include "GameEngine/Animation/AnimationEngine.h"
#include "GameEngine/Physics/PhysicsEngine.h"

extern Scene scene;

extern Blz::Input::Engine input;
extern Blz::AI::Engine AI;
extern Blz::Animation::Engine animation;
extern Blz::Physics::Engine physics;

void Game::Init()
{
	ec.AddContext("When initializing Game");

	Blz::Graphics::Texture fighterTexture("CatFighter.png");

	player.Init(110.0f, 10.0f, fighterTexture);
	enemy.Init(40.0f, 20.0f, fighterTexture);

	scene.AddFighter(&player);
	scene.AddFighter(&enemy);

	bool setAsDefaultAnimation = true;

	this->walkingRight = animation.CreateAnimation(&player, 10, 7);
	this->punching= animation.CreateAnimation(&player, 20, 9);
	this->idle = animation.CreateAnimation(&player, 0, 3, setAsDefaultAnimation);

	this->AIIdle = animation.CreateAnimation(&enemy, 0, 3, setAsDefaultAnimation);

	input.Bind(SDLK_d, &player, std::bind(&Game::MoveRight, this, &player));
	input.Bind(SDLK_a, &player, std::bind(&Game::MoveLeft, this, &player));
	input.Bind(SDLK_SPACE, &player, std::bind(&Game::Jump, this, &player));
	input.Bind(SDLK_p, &player, std::bind(&Game::Punch, this, &player));
}

void Game::Update()
{
	if (player.GetVelocity().GetCurrentState().x > 0)
		animation.PlayAnimation(&player, walkingRight);

	ec.AddContext("When updating Game");
}

void Game::Shutdown()
{

}

void Game::MoveRight(Fighter* const fighter) 
{
	physics.Move(fighter, 90.0f, 0.0f);
}

void Game::MoveLeft(Fighter* const fighter) 
{
	physics.Move(fighter, -90.0f, 0.0f);
}

void Game::Jump(Fighter* const fighter)
{
	physics.Jump(fighter, 50.0f);
}

void Game::Punch(Fighter* const fighter)
{
	animation.PlayAnimation(fighter, punching);
}
