#pragma once
#include "../Scene.h"

namespace Blz
{
	namespace Physics
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