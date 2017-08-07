#include "../Scene.h"
#include "../../Universal/SmallVector.h"
#include "PhysicsSystem.h"

namespace Blz
{
	Fighter MovementSystem(Fighter fighter);
	Blz::SmallVector<Fighter> AABBCollisionSystem(Blz::SmallVector<Fighter> fighters);
	void CheckForCollision(Fighter fighter1, Fighter fighter2);

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

		Blz::SmallVector<Fighter> newFighterStates =  AABBCollisionSystem(fighters);

		scene.fighters.swap(newFighterStates);
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
		Fighter fighter1;
		Fighter fighter2;

		for (Fighter fighter : fighters)
		{
			fighter.collisionBox.SetMaxCoordinateOffset(100.0f, 200.0f);
			fighter.collisionBox.SetMinCoordinateOffset(-100.0f, 0.0f);

			fighter.collisionBox.SetMaxCoordinatePosition(fighter.position.GetCurrentState().x, fighter.position.GetCurrentState().y);
			fighter.collisionBox.SetMinCoordinatePosition(fighter.position.GetCurrentState().x, fighter.position.GetCurrentState().y);

			if (fighter.IsFighterControllable())
				fighter1 = fighter;
			else
				fighter2 = fighter;
		}

		CheckForCollision(fighter1, fighter2);

		return fighters;
	}

	void CheckForCollision(Fighter fighter1, Fighter fighter2)
	{
		glm::vec2 fighter1Max = fighter1.collisionBox.GetCurrentMaxCoordinatePosition();
		glm::vec2 fighter2Max = fighter2.collisionBox.GetCurrentMaxCoordinatePosition();

		glm::vec2 fighter1Min = fighter1.collisionBox.GetCurrentMinCoordinatePosition();
		glm::vec2 fighter2Min = fighter2.collisionBox.GetCurrentMinCoordinatePosition();

		//Exit returning NO intersection between bounding boxes
		if (fighter1Max.x < fighter2Min.x || fighter1Min.x > fighter2Max.x)
			return;
		//Exit returning NO intersection between bounding boxes
		if (fighter1Max.y < fighter2Min.y || fighter1Min.y > fighter2Max.y)
			return;

		//If haven't exited yet then a collision occurred
		LOG("Collision occurred!");
	}
}