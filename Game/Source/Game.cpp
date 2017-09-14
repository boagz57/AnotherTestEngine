#include <SDL.h>
#include <functional>
#include "Game.h"
#include "GameEngine/Scene.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Velocity.h"

extern Scene scene;

void Game::Init()
{
	Blz::Graphics::Texture fighterTexture("Girl.png");

	p_Player = scene.CreateFighter(160.0f, 0.0f, fighterTexture);
	p_AI = scene.CreateFighter(80.0f, 45.0f, fighterTexture);

	this->animation1 = animation.CreateAnimation(p_Player, 0, 7);
	this->animation2 = animation.CreateAnimation(p_AI, 8, 7);

	input.BindAxis(SDLK_d, p_Player, std::bind(&Game::MoveRight, this, p_Player));
	input.BindAxis(SDLK_a, p_Player, std::bind(&Game::MoveLeft, this, p_Player));
	input.BindAxis(SDLK_w, p_Player, std::bind(&Game::MoveUp, this, p_Player));
	input.BindAxis(SDLK_s, p_Player, std::bind(&Game::MoveDown, this, p_Player));
}

void Game::Update()
{
	animation.PlayAnimation(p_Player, animation1);
	animation.PlayAnimation(p_AI, animation2);
}

void Game::Shutdown()
{

}

void Game::MoveRight(Fighter* fighter)
{
	physics.Move(fighter, 0.1f, 0.0f);
}

void Game::MoveLeft(Fighter* fighter)
{
	physics.Move(fighter, -0.1f, 0.0f);
}

void Game::MoveUp(Fighter* fighter)
{
	physics.Move(fighter, 0.0f, 0.1f);
}

void Game::MoveDown(Fighter* fighter)
{
	physics.Move(fighter, 0.0f, -0.1f);
}
