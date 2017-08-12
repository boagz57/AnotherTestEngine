#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "../Vector3D.h"
#include "../Scene.h"

/*
	Responsible for the actual drawing of everything on screen.
*/

namespace Blz
{
	namespace Graphics
	{
		class RenderManager
		{
		public:
			RenderManager();
			~RenderManager();

			void Init(Scene& scene);
			void Update(Scene& scene, ShaderProgram& shader);

		private:
		};
	}
}
