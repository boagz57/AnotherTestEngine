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
				Comp::Position newFighterPosition = [](const Comp::Transform& fighterTransform, Comp::Position& fighterPosition) -> Comp::Position
				{
					fighterPosition.AddBy(fighterTransform.GetCurrentTranslation().x, fighterTransform.GetCurrentTranslation().y);

					return fighterPosition;
				}(fighter.GetTransform(), fighter.GetPosition());

				fighter.Insert(newFighterPosition);
			}
		}
	}
}