#include "../Scene.h"
#include "Components/Position.h"
#include "PhysicsEngine.h"

namespace Blz
{
	namespace Physics
	{
		auto Engine::Move(Fighter* const p_fighter, const sfloat movementInX, const sfloat movementInY) -> void
		{
			if (movementInX != 0.0f)
				p_fighter->velocity.SetVelocityX(movementInX);
			if (movementInY != 0.0f)
				p_fighter->velocity.SetVelocityY(movementInY);
		}

		auto Engine::Jump(Fighter* const p_fighter, const sfloat jumpVelocity) -> void
		{
			sfloat groundLevel = 5.0f;

			if (p_fighter->position.GetCurrentPosition().y == groundLevel)
			{
				p_fighter->velocity.SetVelocityY(jumpVelocity);
			}
			else
			{
				return;
			}
		}

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
				Comp::Position newFighterPosition = [](Comp::Velocity fighterVelocity, Comp::Position fighterPosition, Comp::Movement fighterMovement) -> Comp::Position
				{
					fighterPosition.Add(fighterVelocity.GetCurrentState().x * engineClock.GetPreviousFrameTime(), fighterVelocity.GetCurrentState().y * engineClock.GetPreviousFrameTime());

					return fighterPosition;
				}(fighter->velocity, fighter->position, fighter->movement);


				//Add Gravity 
				Comp::Velocity newFighterVel = [](Comp::Velocity fighterVelocity, Comp::Movement fighterMovement) -> Comp::Velocity
				{
					fighterVelocity.Add(0.0f, (fighterMovement.GetGravity() * engineClock.GetPreviousFrameTime()));

					//Zero out velocity to prevent fighter sliding
					fighterVelocity.ZeroOutX();

					return fighterVelocity;
				}(fighter->velocity, fighter->movement);


				{//Set window borders
					newFighterPosition.ClampMaxPositionTo(160.0f, 90.0f);
					newFighterPosition.ClampMinPositionTo(0.0f, 5.0f);
				}

				//Prevent velocity from going more and more negative when on the ground
				if (newFighterPosition.GetCurrentPosition().y == 5.0f)
					newFighterVel.ZeroOutY();

				fighter->position = newFighterPosition;
				fighter->velocity = newFighterVel;
			}
		}
	}
}