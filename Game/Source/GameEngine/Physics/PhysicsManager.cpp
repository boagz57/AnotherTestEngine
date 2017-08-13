#include "../Scene.h"
#include "Systems/PhysicsSystems.h"
#include "Containers/SmallVector.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{
		PhysicsManager::PhysicsManager()
		{
		}

		PhysicsManager::~PhysicsManager()
		{
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
				TransformComponent newFighterPosition = System::MoveFighter(fighter.GetComponent<TransformComponent>(), fighter.GetComponent<VelocityComponent>());
				VelocityComponent newFighterVelocity = System::ZeroOutVelocity(fighter.GetComponent<VelocityComponent>());

				fighter.Insert<TransformComponent>(newFighterPosition);
				fighter.Insert<VelocityComponent>(newFighterVelocity);
			}
		}
	}
}