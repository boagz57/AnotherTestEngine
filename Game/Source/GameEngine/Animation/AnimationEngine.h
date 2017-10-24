#pragma once
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

			auto Init(Scene& scene) -> void;
			auto Update(Scene& scene) -> void;
		};
	}
}
