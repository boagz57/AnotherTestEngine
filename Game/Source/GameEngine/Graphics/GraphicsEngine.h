#pragma once
#include <GLM/mat4x4.hpp>
#include "ShaderProgram.h"
#include "../Vector3D.h"
#include "Components\Sprite.h"
#include "Containers\Array.h"

class Scene;

namespace Blz::Graphics
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		auto Init(Scene& scene) -> void;
		auto Update(Scene& scene, ShaderProgram& shader) -> void;

	private:
		glm::mat4 orthoProjection;
		Comp::Sprite backGroundSprite;

		GLuint backgroundVBO;
		Array<GLuint, 2> fighterVBOs{};
	};
}
