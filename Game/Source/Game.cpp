#include <SDL.h>
#include <functional>
#include "Game.h"
#include "GameEngine/Scene.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Velocity.h"
#include "Components/Animation.h"

extern Scene scene;

void Game::Init()
{
	ec.AddContext("When initializing Game");

	Blz::Graphics::Texture fighterTexture("Girl.png");

	p_Player = scene.CreateFighter(80.0f, 0.0f, fighterTexture);

	this->walkingUp = animation.CreateAnimation(p_Player, 0, 7);
	this->walkingDown = animation.CreateAnimation(p_Player, 24, 7);
	this->walkingRight = animation.CreateAnimation(p_Player, 8, 7);
	this->walkingLeft= animation.CreateAnimation(p_Player, 16, 7);

	input.BindAxis(SDLK_d, p_Player, std::bind(&Game::MoveRight, this, p_Player));
	input.BindAxis(SDLK_a, p_Player, std::bind(&Game::MoveLeft, this, p_Player));
	input.BindAxis(SDLK_SPACE, p_Player, std::bind(&Game::Jump, this, p_Player));
}

void Game::Update()
{
	ec.AddContext("When updating Game");

	if (p_Player->GetVelocity().GetCurrentState().y > 0)
		animation.PlayAnimation(p_Player, walkingUp);
	else if (p_Player->GetVelocity().GetCurrentState().y < 0)
		animation.PlayAnimation(p_Player, walkingDown);
	else if (p_Player->GetVelocity().GetCurrentState().x > 0)
		animation.PlayAnimation(p_Player, walkingRight);
	else if (p_Player->GetVelocity().GetCurrentState().x < 0)
		animation.PlayAnimation(p_Player, walkingLeft);
}

void Game::Shutdown()
{

}

void Game::MoveRight(Fighter* const fighter) 
{
	physics.Move(fighter, 10.0f, 0.0f);
}

void Game::MoveLeft(Fighter* const fighter) 
{
	physics.Move(fighter, -10.0f, 0.0f);
}

void Game::Jump(Fighter* const fighter)
{
	physics.Jump(fighter, 40.0f);
}