#include "../Scene.h"
#include "Systems/PhysicsSystems.h"
#include "Components/Position.h"
#include "Containers/SmallVector.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{

		void PhysicsManager::Move(Fighter* p_Fighter, sfloat movementInX, sfloat movementInY)
		{
			Comp::Transform fighterTransform = p_Fighter->GetComponent<Comp::Transform>();

			fighterTransform.TranslateBy(movementInX, movementInY);

			p_Fighter->Insert(fighterTransform);
		}

		void PhysicsManager::Init()
		{
		}

		void PhysicsManager::Shutdown()
		{

		}

		void PhysicsManager::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				Comp::Position newFighterPosition = CompSystem::MoveFighter(fighter.GetComponent<Comp::Transform>(), fighter.GetComponent<Comp::Position>());

				fighter.Insert<Comp::Position>(newFighterPosition);
			}
		}
	}
}