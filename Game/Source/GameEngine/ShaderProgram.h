#pragma once
#include "GL\glew.h"

namespace Blz
{
	namespace OpenGL
	{
		class ShaderProgram
		{
		public:
			ShaderProgram();
			~ShaderProgram();
			ShaderProgram(const ShaderProgram& copy) = delete;
			void operator=(const ShaderProgram& copy) = delete;

			void Compile();
			void AddAttribute(Blz::string attributeName);
			void Link();
			void Bind();
			void UnBind();

		public:
			const GLuint programID;

		private:
			GLuint vertexShaderID;
			GLuint fragmentShaderID;
			uint16 numAttributes;

			bool CheckShaderProgramStatus(GLuint programID);
			bool CheckShaderStatus(GLuint shaderID);
		};
	}
}
