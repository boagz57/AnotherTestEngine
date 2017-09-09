#pragma once
#include "AnimationClip.h"
#include "Containers/Vector.h"
#include "Scene.h"

namespace Blz
{
	namespace Animation
	{
		class Engine
		{
		public:
			Engine() = default;
			~Engine() = default;

			void Init(Scene& scene);
			void Update(Scene& scene);

		private:
			
		};
	}
}
