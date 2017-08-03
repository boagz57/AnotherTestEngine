#pragma once
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

		void Update(Scene& scene);
	};
}
