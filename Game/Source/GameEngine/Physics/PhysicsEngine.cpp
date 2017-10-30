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

	static auto PhysicsSystem(Comp::Velocity vel, Comp::Position pos, Comp::Movement move) -> Components;

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
			[&fighter](const Comp::Velocity& fighterVelocity, const Comp::Position& fighterPosition, const Comp::Movement& fighterMovement) -> void 
			{
				auto[updatedFighterVelocity, updatedFighterPosition, updatedFighterMovement] = 
					PhysicsSystem(fighterVelocity, fighterPosition, fighterMovement);

				fighter->velocity = updatedFighterVelocity;
				fighter->position = updatedFighterPosition;
				fighter->movement = updatedFighterMovement;

			}(fighter->velocity, fighter->position, fighter->movement);
		};
	}

	auto PhysicsSystem(Comp::Velocity fighterVelocity, Comp::Position fighterPosition, Comp::Movement fighterMovement) -> Components
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
	}
}