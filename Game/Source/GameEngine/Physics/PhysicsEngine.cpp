#include "../Scene.h"
#include "Components/Position.h"
#include "PhysicsEngine.h"

namespace Blz
{
	namespace Physics
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

			for (Fighter& fighter : scene.fighters)
			{
				//Move fighter by current translation
				Comp::Position newFighterPosition = [](const Comp::Velocity& fighterVelocity, Comp::Position fighterPosition) -> Comp::Position
				{
					fighterPosition.Add(fighterVelocity.GetCurrentState().x * engineClock.GetFrameTime(),fighterVelocity.GetCurrentState().y * engineClock.GetFrameTime());

					return fighterPosition;
				}(fighter.GetVelocity(), fighter.GetPosition());


				Comp::Velocity newFighterVel = [](Comp::Velocity fighterVelocity) -> Comp::Velocity
				{
					fighterVelocity.ZeroOut();

					return fighterVelocity;
				}(fighter.GetVelocity());


				{//Stop fighter from moving outside window bounds
					newFighterPosition.ClampMaxPositionTo(160.0f, 90.0f);

					//Create higher Y bounds to simulate the ground of a level
					newFighterPosition.ClampMinPositionTo(0.0f, 5.0f);
				}

				fighter.Insert(newFighterPosition);
				fighter.Insert(newFighterVel);
			}
		}
	}
}