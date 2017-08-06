#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "../Vector3D.h"
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

		private:
		};
	}
}
