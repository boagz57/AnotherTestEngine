#include <GL\glew.h>
#include <gtest\gtest.h>
#include "Scene.h"
#include "Fighter.h"
#include "GameEngine\Physics\PhysicsEngine.h"
#include "GameEngine\Physics\GameLogic\PhysicsGameLogic.h"

struct PhysicsEngineTest : public testing::Test
{
	Blz::Physics::Engine physics;
	Fighter fighter;
	Scene scene;
};

TEST_F(PhysicsEngineTest, DoesPhysicsUpdateFighterVelocityProperly_True)
{
	scene.AddFighter(&fighter);

	BlzPhysics::Move(&fighter, 0.0, 3.0f);

	physics.Init();

	physics.Update(scene);
}