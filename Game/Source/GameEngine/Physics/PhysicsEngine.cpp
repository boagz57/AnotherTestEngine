#include "../Scene.h"
#include "Components/Position.h"
#include "PhysicsEngine.h"

namespace Blz::Physics
{
	struct Components
	{
		Comp::Velocity velocity;
		Comp::Position position;
		Comp::Movement movement;
	};

	auto Engine::Init() -> void
	{
	}

	auto Engine::Shutdown() -> void
	{

	}

	auto Engine::Update(Scene& scene) -> void
	{
		ec.AddContext("When updating Physics engine");

		for (Fighter* fighter : scene.fighters)
		{
			//All accepted components of Physics system
			auto [updatedFighterVelocity, updatedFighterPosition, updatedFighterMovement] = [&fighter](Comp::Velocity fighterVelocity, Comp::Position fighterPosition, Comp::Movement fighterMovement) -> Components
			{
				fighterPosition.Add(fighterVelocity.GetCurrentState().x * engineClock.GetPreviousFrameTime(), fighterVelocity.GetCurrentState().y * engineClock.GetPreviousFrameTime());

				fighterVelocity.Add(0.0f, (fighterMovement.GetGravity() * engineClock.GetPreviousFrameTime()));

				fighterPosition.ClampMaxPositionTo(c_levelBorderMaxX, c_levelBorderMaxY);
				fighterPosition.ClampMinPositionTo(c_levelBorderMinX, c_groundLevel);

				//Prevent velocity from going more and more negative when on the ground
				if (fighterPosition.GetCurrentPosition().y == c_groundLevel)
					fighterVelocity.ZeroOutY();

				return { fighterVelocity, fighterPosition, fighterMovement };

			}(fighter->velocity, fighter->position, fighter->movement);

			fighter->velocity = updatedFighterVelocity;
			fighter->position = updatedFighterPosition;
			fighter->movement = updatedFighterMovement;
		};
	}
}