#pragma once

#include "GL\glew.h"

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

			void Init(Blz::string vertexShaderFilePath, Blz::string fragmentShaderFilePath);
			void Compile();
			void AddAttribute(Blz::string attributeNameFromShaderFile);
			GLuint GetUniformLocation(Blz::string uniformNameFromShaderFile);
			void Link();
			void Bind();
			void UnBind();

		public:
			GLuint programID;

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
