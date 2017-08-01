#pragma once
#include "ShaderProgram.h"
#include "../Fighter.h"

namespace Blz
{
	namespace Graphics
	{
		namespace RenderSystem
		{
			void Init(Fighter& fighter);
			void Update(Fighter& fighter, ShaderProgram& shader);
		}
	}
}
