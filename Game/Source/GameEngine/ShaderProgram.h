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
			void AddAttribute(Blz::string attributeNameFromShader);
			GLuint GetUniformLocation(Blz::string uniformNameFromShader);
			void Link();
			void Bind();
			void UnBind();

		public:
			const GLuint programID;

		private:
			Blz::string vertexShaderFile;
			Blz::string fragmentShaderFile;
			GLuint vertexShaderID;
			GLuint fragmentShaderID;

			uint16 numAttributes;

			bool CheckShaderProgramStatus(GLuint programID);
			bool CheckShaderStatus(GLuint shaderID);
		};
	}
}
