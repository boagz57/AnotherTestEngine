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

	Blz::Graphics::Texture fighterTexture("CatFighter.png");

	p_Player = scene.CreateFighter(80.0f, 30.0f, fighterTexture);
	p_AI = scene.CreateFighter(45.0f, 0.0f, fighterTexture);

	this->walkingRight = animation.CreateAnimation(p_Player, 10, 7);
	this->punching= animation.CreateAnimation(p_Player, 20, 9);

	input.Bind(SDLK_d, p_Player, std::bind(&Game::MoveRight, this, p_Player));
	input.Bind(SDLK_a, p_Player, std::bind(&Game::MoveLeft, this, p_Player));
	input.Bind(SDLK_SPACE, p_Player, std::bind(&Game::Jump, this, p_Player));
	input.Bind(SDLK_p, p_Player, std::bind(&Game::Punch, this, p_Player));
}

void Game::Update()
{
	ec.AddContext("When updating Game");

	if (p_Player->GetVelocity().GetCurrentState().x > 0)
		animation.PlayAnimation(p_Player, walkingRight);
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
