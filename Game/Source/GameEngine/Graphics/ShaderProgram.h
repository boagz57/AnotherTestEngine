#pragma once

#include "GL\glew.h"

namespace Blz::Graphics
{
	class ShaderProgram
	{
	public:
		ShaderProgram() = default;
		~ShaderProgram();
		ShaderProgram(const ShaderProgram& copy) = delete;
		void operator=(const ShaderProgram& copy) = delete;

		auto Init(Blz::string vertexShaderFilePath, Blz::string fragmentShaderFilePath) -> void;
		auto Compile() -> void;
		auto AddAttribute(Blz::string attributeNameFromShaderFile) -> void;
		auto GetUniformLocation(Blz::string uniformNameFromShaderFile)->GLuint;
		auto Link() -> void;
		auto Bind() -> void;
		auto UnBind() -> void;

	public:
		GLuint programID;

	private:
		Blz::string vertexShaderFile;
		Blz::string fragmentShaderFile;
		GLuint vertexShaderID = 0;
		GLuint fragmentShaderID = 0;

		uint16 numAttributes = 0;

		auto CheckShaderProgramStatus(GLuint programID) -> bool;
		auto CheckShaderStatus(GLuint shaderID) -> bool;
	};
}
