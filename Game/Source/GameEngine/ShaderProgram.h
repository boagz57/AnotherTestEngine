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

			void CompileAndLink();
			void Bind();
			void UnBind();

		private:
			GLuint programID;
			GLuint vertexShaderID;
			GLuint fragmentShaderID;

			bool CheckShaderProgramStatus(GLuint programID);
			bool CheckShaderStatus(GLuint shaderID);
		};
	}
}
