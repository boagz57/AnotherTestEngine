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
				Comp::Position newFighterPosition = [](const Comp::Transform& fighterTransform, Comp::Position fighterPosition) -> Comp::Position
				{
					fighterPosition.Add(fighterTransform.GetCurrentTranslation().x, fighterTransform.GetCurrentTranslation().y);

					return fighterPosition;
				}(fighter.GetTransform(), fighter.GetPosition());


				//Zero out translation
				Comp::Transform newFighterTransform = [](Comp::Transform fighterTransform) -> Comp::Transform
				{
					fighterTransform.ZeroOut();

					return fighterTransform;
				}(fighter.GetTransform());


				{//Stop fighter from moving outside window bounds
					newFighterPosition.ClampMaxPositionTo(160.0f, 90.0f);
					newFighterPosition.ClampMinPositionTo(0.0f, 0.0f);
				}

				fighter.Insert(newFighterPosition);
				fighter.Insert(newFighterTransform);
			}
		}
	}
}