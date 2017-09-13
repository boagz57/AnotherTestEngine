#include <SDL.h>
#include "Game.h"
#include "GameEngine/Scene.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Velocity.h"

extern Scene scene;
extern Blz::Physics::Manager physics;

void MoveRight(Fighter* fighter);

void Game::Init()
{
	Blz::Graphics::Texture fighterTexture("Girl.png");

	p_Player = scene.CreateFighter(160.0f, 0.0f, fighterTexture);
	p_AI = scene.CreateFighter(80.0f, 45.0f, fighterTexture);

	this->animation1 = animation.CreateAnimation(p_Player, 0, 7);
	this->animation2 = animation.CreateAnimation(p_AI, 8, 7);

	input.BindAxis(SDLK_d, p_Player, &MoveRight);
}

void Game::Update()
{
	animation.PlayAnimation(p_Player, animation1);
	animation.PlayAnimation(p_AI, animation2);
}

void Game::Shutdown()
{

}

void MoveRight(Fighter* fighter)
{
	physics.Move(fighter, 0.1f, 0.0f);
}
