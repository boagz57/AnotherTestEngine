#pragma once
#include "../Scene.h"

namespace Blz
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();

		void Init();
		void Shutdown();
		void Update(Scene& scene);
	};
}