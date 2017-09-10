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

	input.SetFighterToBeControllable(p_Player);

	uint16 animation1 = animation.CreateAnimation(p_Player, 0, 7);
	uint16 animation2 = animation.CreateAnimation(p_AI, 0, 7);
	animation.PlayAnimation(p_Player, animation1);
	animation.PlayAnimation(p_AI, animation1);
}

void Game::Update()
{
	physics.Move(p_Player, -0.1f, 0.1f);
}

void Game::Shutdown()
{

}
