#include "../Scene.h"
#include "Components/Position.h"
#include "PhysicsEngine.h"

namespace Blz
{
	namespace Physics
	{
		static const sfloat c_groundLevel = 5.0f;

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
					fighter->position.ClampMaxPositionTo(160.0f, 90.0f);
					fighter->position.ClampMinPositionTo(0.0f, c_groundLevel);
				}

				//Prevent velocity from going more and more negative when on the ground
				if (fighter->position.GetCurrentPosition().y == c_groundLevel)
					fighter->velocity.ZeroOutY();
			}
		}
	}
}