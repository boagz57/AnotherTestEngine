#pragma once
#include <GLM/mat4x4.hpp>
#include "ShaderProgram.h"
#include "Window.h"
#include "../Vector3D.h"
#include "../Scene.h"
#include "Components\Sprite.h"
#include "Containers\Array.h"

/*
	Responsible for the actual drawing of everything on screen.
*/

namespace Blz::Graphics
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		auto Init(Scene& scene, const Window& window) -> void;
		auto Update(Scene& scene, ShaderProgram& shader, const Window& window) -> void;

	private:
		glm::mat4 orthoProjection;
		Comp::Sprite backGroundSprite;

		GLuint backgroundVBO;
		Array<GLuint, 2> fighterVBOs;

	};
}
