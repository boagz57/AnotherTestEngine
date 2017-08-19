#pragma once
#include <GL/glew.h>
#include "Containers/Map.h"
#include "ShaderProgram.h"

class ShaderManager
{
public:
	ShaderManager() = default;
	~ShaderManager() = default;

	void CreateProgram(const Blz::string& shaderName, const std::string& vertexShaderFileName, const std::string& FragmentShaderFileName);

	static const GLuint GetShader(const Blz::string& shaderName);

private:
	Blz::Map<std::string, GLuint> shaderPrograms;
};

