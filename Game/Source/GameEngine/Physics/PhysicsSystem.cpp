#include "../Scene.h"
#include "../../Universal/SmallVector.h"
#include "PhysicsSystem.h"

namespace Blz
{
	Fighter MovementSystem(Fighter fighter);
	Blz::SmallVector<Fighter> AABBCollisionSystem(Blz::SmallVector<Fighter> fighters);

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
		//Set how much fighter will be translated within world
		fighter.transform.TranslatePosition(fighter.velocity.GetCurrentState().x, fighter.velocity.GetCurrentState().y);

		//Set fighters new world position
		fighter.position.Add(fighter.velocity.GetCurrentState().x, fighter.velocity.GetCurrentState().y);

		//To stop fighter movement from continuing to move in the direction of input
		fighter.velocity.ZeroOut();

		return fighter;
	}

	Blz::SmallVector<Fighter> AABBCollisionSystem(Blz::SmallVector<Fighter> fighters)
	{
		Fighter* fighter1 = nullptr;
		Fighter* fighter2 = nullptr;

		for (Fighter fighter : fighters)
		{
			fighter.collisionBox.SetMaxCoordinateOffset(100.0f, 100.0f);
			fighter.collisionBox.SetMinCoordinateOffset(-100.0f, 0.0f);
		}

		for (uint16 i = 0; i < fighters.size(); ++i)
		{
			if (fighters.size() == 1)
				fighter1 = &fighters.at(i);
			else
				fighter2 = &fighters.at(i);
		}

		return fighters;
	}
}