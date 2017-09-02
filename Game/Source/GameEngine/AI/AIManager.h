#pragma once
#include "../Scene.h"

namespace Blz
{
	namespace AI
	{
		class AIManager
		{
		public:
			AIManager() = default;
			~AIManager() = default;

			void Init();
			void Shutdown();

			void Update(Scene& scene);
		};
	}
}
