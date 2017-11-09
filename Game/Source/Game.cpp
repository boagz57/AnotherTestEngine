#include <SDL.h>
#include <functional>
#include "Game.h"
#include "GameEngine/Scene.h"
#include "GameEngine/AI/AIEngine.h"
#include "GameEngine/Input/InputEngine.h"
#include "GameEngine/Animation/AnimationEngine.h"
#include "GameEngine/Physics/GameLogic/PhysicsGameLogic.h"
#include "GameEngine/Input/GameLogic/InputGameLogic.h"
#include "GameEngine/Animation/GameLogic/AnimationGameLogic.h"

extern Scene scene;

void Game::Init()
{
	ec.AddContext("When initializing Game");

	Blz::Graphics::Texture fighterTexture("CatFighter.png");
	Blz::Graphics::Texture backgroundTexture("BackgroundStage.png");

	player.Init(110.0f, 10.0f, fighterTexture);
	enemy.Init(40.0f, 10.0f, fighterTexture);

	scene.AddFighter(&player);
	scene.AddFighter(&enemy);
	scene.SetBackground(backgroundTexture);

	bool setAsDefaultAnimation = true;

	this->walkingRight = BlzAnimation::CreateAnimation(&player, 10, 7);
	this->punching= BlzAnimation::CreateAnimation(&player, 20, 9);
	this->idle = BlzAnimation::CreateAnimation(&player, 0, 3, setAsDefaultAnimation);

	this->AIIdle = BlzAnimation::CreateAnimation(&enemy, 0, 3, setAsDefaultAnimation);

	BlzInput::Bind(SDLK_d, &player, std::bind(&Game::MoveRight, this, &player));
	BlzInput::Bind(SDLK_a, &player, std::bind(&Game::MoveLeft, this, &player));
	BlzInput::Bind(SDLK_SPACE, &player, std::bind(&Game::Jump, this, &player));
	BlzInput::Bind(SDLK_p, &player, std::bind(&Game::Punch, this, &player));
}

void Game::Update()
{
	if (player.GetVelocity().GetCurrentState().x > 0)
		BlzAnimation::PlayAnimation(&player, walkingRight);


	ec.AddContext("When updating Game");
}

void Game::Shutdown()
{

}

void Game::MoveRight(Fighter* const fighter) 
{
	BlzPhysics::Move(fighter, 100.0f, 0.0f);
}

void Game::MoveLeft(Fighter* const fighter) 
{
	BlzPhysics::Move(fighter, -100.0f, 0.0f);
}

void Game::Jump(Fighter* const fighter)
{
	BlzPhysics::Jump(fighter, 200.0f);
}

void Game::Punch(Fighter* const fighter)
{
	BlzAnimation::PlayAnimation(fighter, punching);
}
