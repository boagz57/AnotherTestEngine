#pragma once
#include "ShaderProgram.h"
#include "../Scene.h"

namespace Blz
{
	namespace Graphics
	{
		class RenderSystem
		{
		public:
			RenderSystem();
			~RenderSystem();

			void Init(Scene& scene);
			void Update(Scene& scene, ShaderProgram& shader);
		};
	}
}
