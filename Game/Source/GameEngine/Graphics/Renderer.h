#pragma once
#include "ShaderProgram.h"
#include "../Fighter.h"
#include "Sprite.h"

namespace Blz
{
	namespace Graphics
	{
		class Renderer
		{
		public:
			Renderer();
			~Renderer();

			void Init();
			void Draw(Fighter& fighterToDraw);

		private:
			ShaderProgram shaderProgram;
		};
	}
}
