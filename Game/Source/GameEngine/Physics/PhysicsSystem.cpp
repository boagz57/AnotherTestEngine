#include "../Scene.h"
#include "PhysicsSystem.h"

namespace Blz
{
	Fighter MovementSystem(Fighter fighter);

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

	Scene PhysicsSystem::Update(Scene scene)
	{
		for (Fighter& fighter : scene.fighters)
		{
			Fighter newFighterState = MovementSystem(fighter);
			
			fighters.push_back(newFighterState);
		}

		scene.fighters.swap(fighters);
		fighters.clear();

		return scene;
	}

	Fighter MovementSystem(Fighter fighter)
	{
		fighter.position.Add(fighter.velocity.GetCurrentState().x, fighter.velocity.GetCurrentState().y);

		//To stop fighter movement from continuing to move in the direction of input
		fighter.velocity.ZeroOut();

		return fighter;
	}
}