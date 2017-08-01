#pragma once
#include "ShaderProgram.h"
#include "../Scene.h"

namespace Blz
{
	namespace Graphics
	{
		namespace RenderSystem
		{
			void Init(Scene& scene);
			void Update(Scene& scene, ShaderProgram& shader);
		}
	}
}
