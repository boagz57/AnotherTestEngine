#pragma once
#include "../Scene.h"

namespace Blz
{
	namespace Physics
	{
		class PhysicsManager
		{
		public:
			PhysicsManager() = default;
			~PhysicsManager() = default;

			void Move(Fighter* fighter, sfloat movementInX, sfloat movementInY);

			void Init();
			void Shutdown();
			void Update(Scene& scene);
		};
	}
}