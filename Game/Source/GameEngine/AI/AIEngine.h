#pragma once
#include "../Scene.h"

namespace Blz
{
	namespace AI
	{
		class Engine
		{
		public:
			Engine() = default;
			~Engine() = default;

			void Init();
			void Shutdown();

			void Update(Scene& scene);
		};
	}
}
