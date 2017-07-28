#pragma once
#include "ShaderProgram.h"
#include "../Scene.h"
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
			void Draw(Scene& sceneToDraw);

		private:
			ShaderProgram shaderProgram;
		};
	}
}
