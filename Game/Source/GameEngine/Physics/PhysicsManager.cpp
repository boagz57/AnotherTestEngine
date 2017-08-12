#include "../Scene.h"
#include "Systems\MovementSystem.h"
#include "../../Universal/SmallVector.h"
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

		Scene PhysicsManager::Update(Scene scene)
		{
			Blz::SmallVector<Fighter> newFighterStates;

			for (Fighter& fighter : scene.fighters)
			{
				TransformComponent newComp = System::MovementSystem(fighter.GetComponent<TransformComponent>(), fighter.GetComponent<VelocityComponent>());
				fighter.Insert<TransformComponent>(newComp);
			}

			return scene;
		}
	}
}