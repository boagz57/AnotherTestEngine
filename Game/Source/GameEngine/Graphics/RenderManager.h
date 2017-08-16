#pragma once
#include <GLM/mat4x4.hpp>
#include "ShaderProgram.h"
#include "Window.h"
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

			void Init(Scene& scene, Window& window);
			void Update(Scene& scene, ShaderProgram& shader);

		private:
			glm::mat4 orthoProjection;
		};
	}
}
