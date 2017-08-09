#include "../Scene.h"
#include "Systems\AABBCollisionSystem.h"
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
			for (Fighter& fighter : scene.fighters)
			{
				Fighter newFighterState = MovementSystem(fighter);

				fighters.push_back(newFighterState);
			}

			Blz::SmallVector<Fighter> newFighterStates = AABBCollisionSystem(fighters);

			scene.fighters.swap(newFighterStates);
			fighters.clear();

			return scene;
		}
	}
}