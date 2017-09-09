#include "Game.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Velocity.h"
#include "GameEngine/Animation/AnimationEngine.h"
#include "GameEngine/Input/InputEngine.h"
#include "GameEngine/Physics/PhysicsEngine.h"

extern Scene scene;

void Game::Init()
{
	Blz::Graphics::Texture fighterTexture("Girl.png");

	p_Player = scene.CreateFighter(160.0f, 0.0f, fighterTexture);
	p_AI = scene.CreateFighter(80.0f, 45.0f, fighterTexture);

	input.SetFighterToBeControllable(p_Player);
}

void Game::Update()
{
	physics.Move(p_Player, -0.1f, 0.1f);
}

void Game::Shutdown()
{

}
