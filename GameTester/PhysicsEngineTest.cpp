#include <GL\glew.h>
#include <gtest\gtest.h>
#include "Components\Velocity.h"
#include "Scene.h"
#include "BlueGod.h"
#include "GameEngine\Physics\PhysicsEngine.h"
#include "GameEngine\Physics\GameLogic\PhysicsGameLogic.h"

struct PhysicsEngineTest : public testing::Test
{
	Blz::Physics::Engine physics;
	Scene scene;
	BlueGod player1;
};

TEST_F(PhysicsEngineTest, DoesPhysicsUpdateFighterVelocityProperly_True)
{
}