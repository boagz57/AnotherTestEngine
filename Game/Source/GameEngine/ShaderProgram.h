#pragma once

#include "GL\glew.h"

namespace Blz
{
	namespace OpenGL
	{
		class ShaderProgram
		{
		public:
			ShaderProgram(Blz::string vertexShaderFilePath, Blz::string fragmentShaderFilePath);
			~ShaderProgram();
			ShaderProgram(const ShaderProgram& copy) = delete;
			void operator=(const ShaderProgram& copy) = delete;

			void Compile();
			void AddAttribute(Blz::string attributeNameFromShaderFile);
			GLuint GetUniformLocation(Blz::string uniformNameFromShaderFile);
			void Link();
			void Bind();
			void UnBind();

		public:
			const GLuint programID = glCreateProgram();

		private:
			Blz::string vertexShaderFile;
			Blz::string fragmentShaderFile;
			GLuint vertexShaderID = 0;
			GLuint fragmentShaderID = 0;

			uint16 numAttributes = 0;

			bool CheckShaderProgramStatus(GLuint programID);
			bool CheckShaderStatus(GLuint shaderID);
		};
	}
}
