#pragma once
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

			void Init(Sprite& sprite);
			void Draw();

		private:
			GLuint VBOID = 0;
			Sprite sprite;
		};
	}
}
