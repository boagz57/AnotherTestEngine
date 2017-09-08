#include "Game.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Velocity.h"
#include "GameEngine/Animation/AnimationManager.h"

extern Blz::Animation::AnimationManager animation;
extern Scene scene;

void Game::Init()
{
	uint16 walkingUp = animation.CreateAnimation(8, 7);
	animationMap[AnimationState::WALKINGUP] = walkingUp;

	Blz::Graphics::Texture fighterTexture("Girl.png");

	p_Player = scene.CreatePlayerFighter(160.0f, 0.0f, fighterTexture);
	p_AI = scene.CreateAIFighter(80.0f, 45.0f, fighterTexture);

	Comp::Input playerInput = p_Player->GetComponent<Comp::Input>();
	playerInput.MakeFighterControllable();

	p_Player->Insert(playerInput);
}

void Game::Update()
{
	Comp::Transform newTransform = p_Player->GetComponent<Comp::Transform>();

	if (p_Player->GetComponent<Comp::Velocity>().GetCurrentState().x > 0)
		newTransform.TranslateBy(0.1f, 0.0f);
	else if (p_Player->GetComponent<Comp::Velocity>().GetCurrentState().x < 0)
		newTransform.TranslateBy(-0.1f, 0.0f);

	animation.PlayAnimation(animationMap[AnimationState::WALKINGUP]);

	p_Player->Insert(newTransform);
}

void Game::Shutdown()
{

}
