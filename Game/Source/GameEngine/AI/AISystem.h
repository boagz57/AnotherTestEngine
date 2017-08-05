#pragma once
#include "../../Universal/SmallVector.h"
#include "../Scene.h"

namespace Blz
{
	class AISystem
	{
	public:
		AISystem();
		~AISystem();

		void Init();
		void Shutdown();

		Scene Update(Scene scene);

	private:
		Blz::SmallVector<Fighter> fighters;
	};
}
