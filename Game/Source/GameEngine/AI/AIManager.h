#pragma once
#include "../../Universal/SmallVector.h"
#include "../Scene.h"

namespace Blz
{
	namespace AI
	{
		class AIManager
		{
		public:
			AIManager();
			~AIManager();

			void Init();
			void Shutdown();

			void Update(Scene& scene);
		};
	}
}
