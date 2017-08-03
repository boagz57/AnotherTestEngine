#pragma once
#include <GL/glew.h>
#include "../../Universal/Map.h"
#include "ShaderProgram.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void CreateProgram(const std::string& shaderName, const std::string& vertexShaderFileName, const std::string& FragmentShaderFileName);

	static const GLuint GetShader(const std::string& shaderName);

private:
	Blz::Map<std::string, GLuint> shaderPrograms;
};

