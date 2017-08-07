#pragma once
#include "../../Universal/SmallVector.h"
#include "../Scene.h"

namespace Blz
{
	namespace Physics
	{
		class MainSystem
		{
		public:
			MainSystem();
			~MainSystem();

			void Init();
			void Shutdown();
			Scene Update(Scene scene);

		private:
			Blz::SmallVector<Fighter> fighters;
		};
	}
}