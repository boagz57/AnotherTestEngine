#include "../Scene.h"
#include "PhysicsSystem.h"

namespace Blz
{
	PhysicsSystem::PhysicsSystem()
	{
	}

	PhysicsSystem::~PhysicsSystem()
	{
	}

	void PhysicsSystem::Init()
	{

	}

	void PhysicsSystem::Shutdown()
	{

	}

	void PhysicsSystem::Update(Scene& scene)
	{
		for (Fighter& fighter : scene.fighters)
		{
			fighter.position.Add(fighter.velocity.GetCurrentState().x, fighter.velocity.GetCurrentState().y);

			//To stop fighter movement from continuing to move in the direction of input
			fighter.velocity.ZeroOut();
		}
	}
}