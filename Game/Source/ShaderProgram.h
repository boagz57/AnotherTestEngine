#pragma once

#include "GL\glew.h"
#include <string>

namespace Blz
{
	namespace Graphics
	{
		class ShaderProgram
		{
		public:
			ShaderProgram() = default;
			~ShaderProgram();
			ShaderProgram(const ShaderProgram& copy) = delete;
			void operator=(const ShaderProgram& copy) = delete;

			auto Init(std::string vertexShaderFilePath, std::string fragmentShaderFilePath) -> void;
			auto Compile() -> void;
			auto AddAttribute(std::string attributeNameFromShaderFile) -> void;
			auto GetUniformLocation(std::string uniformNameFromShaderFile) -> GLuint;
			auto Link() -> void;
			auto Bind() -> void;
			auto UnBind() -> void;

		public:
			GLuint programID;

		private:
			std::string vertexShaderFile;
			std::string fragmentShaderFile;
			GLuint vertexShaderID = 0;
			GLuint fragmentShaderID = 0;

			uint16 numAttributes = 0;

			auto CheckShaderProgramStatus(GLuint programID) -> bool;
			auto CheckShaderStatus(GLuint shaderID) -> bool;
		};
	}
}
