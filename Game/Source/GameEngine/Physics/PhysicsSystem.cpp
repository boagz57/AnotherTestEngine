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
			glm::vec3 fighterPosition = fighter.GetPosition();
			glm::vec3 fighterVelocity = fighter.GetVelocity();
			fighter.AddToPosition(fighterVelocity.x, fighterVelocity.y, fighterVelocity.z);
			fighter.SetVelocity(0, 0);
		}
	}
}