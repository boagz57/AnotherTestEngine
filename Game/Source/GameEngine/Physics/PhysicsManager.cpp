#include "../Scene.h"
#include "Systems/PhysicsSystems.h"
#include "Containers/SmallVector.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{
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
				Comp::Transform newFighterTranslation = CompSystem::MoveFighter(fighter.GetComponent<Comp::Transform>(), fighter.GetComponent<Comp::Velocity>());

				fighter.Insert<Comp::Transform>(newFighterTranslation);
			}
		}
	}
}