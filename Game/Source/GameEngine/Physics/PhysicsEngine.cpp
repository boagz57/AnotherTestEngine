#include "../Scene.h"
#include "Components/Position.h"
#include "PhysicsEngine.h"

namespace Blz::Physics
{
	auto Engine::Init() -> void
	{
	}

	auto Engine::Shutdown() -> void
	{

	}

	auto Engine::Update(Scene& scene) -> Components
	{
		ec.AddContext("When updating Physics engine");

		for (Fighter* fighter : scene.fighters)
		{
			auto PhysicsSystem = [](Comp::Velocity fighterVelocity, Comp::Position fighterPosition, Comp::Movement fighterMovement) -> Components
			{
				//Move fighter 
				fighterPosition.Add(fighterVelocity.GetCurrentState().x * engineClock.GetPreviousFrameTime(), fighterVelocity.GetCurrentState().y * engineClock.GetPreviousFrameTime());

				//Apply Gravity 
				fighterVelocity.Add(0.0f, (fighterMovement.GetGravity() * engineClock.GetPreviousFrameTime()));

				{//Set window borders
					fighterPosition.ClampMaxPositionTo(c_levelBorderMaxX, c_levelBorderMaxY);
					fighterPosition.ClampMinPositionTo(c_levelBorderMinX, c_groundLevel);
				}

				//Prevent velocity from going more and more negative when on the ground
				if (fighterPosition.GetCurrentPosition().y == c_groundLevel)
					fighterVelocity.ZeroOutY();

				return { fighterVelocity, fighterPosition, fighterMovement };
			};

			auto[updatedFighterVelocity, updatedFighterPosition, updatedFighterMovement] = 
				PhysicsSystem(fighter->velocity, fighter->position, fighter->movement);

			fighter->velocity = updatedFighterVelocity;
			fighter->position = updatedFighterPosition;
			fighter->movement = updatedFighterMovement;

		}
	}
}