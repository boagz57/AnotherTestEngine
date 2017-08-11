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
				glm::vec2 newPosition = MovementSystem(fighter.transform, fighter.velocity);
				fighter.Insert(new TransformComponent(newPosition));
			}

			return scene;
		}
	}
}