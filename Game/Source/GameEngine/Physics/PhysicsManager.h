#pragma once
#include "../Scene.h"

namespace Blz
{
	namespace Physics
	{
		class PhysicsManager
		{
		public:
			PhysicsManager();
			~PhysicsManager();

			void Init();
			void Shutdown();
			void Update(Scene& scene);
		};
	}
}