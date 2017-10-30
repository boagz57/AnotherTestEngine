#include <GL\glew.h>
#include <gtest\gtest.h>
#include "Components\Velocity.h"
#include "Scene.h"
#include "BlueGod.h"
#include "GameEngine\Physics\PhysicsEngine.h"
#include "GameEngine\Physics\PhysicsEngine.cpp"
#include "GameEngine\Physics\GameLogic\PhysicsGameLogic.h"

struct PhysicsEngineTest : public testing::Test
{
	Blz::Physics::Engine physics;
	Scene scene;
	BlueGod player1;
};

TEST_F(PhysicsEngineTest, DoesPhysicsUpdateFighterVelocityProperly_True)
{
	scene.AddFighter(&player1);

	BlzPhysics::Move(&player1, 0.0, 3.0f);

	physics.Init();

	auto[updatedVelocity, updatedPosition, updatedMovment] = Blz::Physics::PhysicsSystem(player1.GetVelocity(), player1.GetPosition(), player1.GetMovement());
}