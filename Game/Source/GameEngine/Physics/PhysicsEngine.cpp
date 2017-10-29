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

	auto Engine::Update(Scene& scene) -> void
	{
		ec.AddContext("When updating Physics engine");

		for (Fighter* fighter : scene.fighters)
		{
			//Move fighter 
			[](const Comp::Velocity& fighterVelocity, Comp::Position& fighterPosition, const Comp::Movement& fighterMovement) -> void
			{
				fighterPosition.Add(fighterVelocity.GetCurrentState().x * engineClock.GetPreviousFrameTime(), fighterVelocity.GetCurrentState().y * engineClock.GetPreviousFrameTime());

			}(fighter->velocity, fighter->position, fighter->movement);


			//Apply Gravity 
			[](Comp::Velocity& fighterVelocity, const Comp::Movement& fighterMovement) -> void
			{
				fighterVelocity.Add(0.0f, (fighterMovement.GetGravity() * engineClock.GetPreviousFrameTime()));

			}(fighter->velocity, fighter->movement);


			{//Set window borders
				fighter->position.ClampMaxPositionTo(c_levelBorderMaxX, c_levelBorderMaxY);
				fighter->position.ClampMinPositionTo(c_levelBorderMinX, c_groundLevel);
			}

			//Prevent velocity from going more and more negative when on the ground
			if (fighter->position.GetCurrentPosition().y == c_groundLevel)
				fighter->velocity.ZeroOutY();
		}
	}
}