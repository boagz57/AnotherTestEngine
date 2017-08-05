#pragma once
#include "../../Universal/SmallVector.h"
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
		Scene Update(Scene scene);

	private:
		Blz::SmallVector<Fighter> fighters;
	};
}