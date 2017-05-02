#include <fstream>
#include <string>
#include "GL\glew.h"
#include "ShaderProgram.h"

namespace Blz
{
	namespace OpenGL
	{
		//Class Helper functions
		std::string ReadShaderSource(const char8* c_ShaderFilePath, const char8* c_TypeOfShader);

		ShaderProgram::ShaderProgram() :
			programID(glCreateProgram()),
			vertexShaderID(0),
			fragmentShaderID(0),
			numAttributes(0)
		{
		}

		ShaderProgram::~ShaderProgram()
		{
			glDeleteProgram(programID);
		}

		void ShaderProgram::Compile()
		{
			//Create GL Shaders
			vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			const GLchar* cAdapter[1];

			//Add source or text file to shader object
			std::string temp = ReadShaderSource("Source/GameEngine/Shaders/VertexShader.glsl", "Vertex").c_str();
			cAdapter[0] = temp.c_str();
			glShaderSource(vertexShaderID, 1, cAdapter, 0);

			temp = ReadShaderSource("Source/GameEngine/Shaders/FragmentShader.glsl", "Fragment").c_str();
			cAdapter[0] = temp.c_str();
			glShaderSource(fragmentShaderID, 1, cAdapter, 0);

			glCompileShader(vertexShaderID);
			glCompileShader(fragmentShaderID);

			if (!CheckShaderStatus(vertexShaderID) || !CheckShaderStatus(fragmentShaderID))
				return;
		}

		void ShaderProgram::AddAttribute(Blz::string attributeName)
		{
			glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
		}

		void ShaderProgram::Link()
		{
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);

			glLinkProgram(programID);

			if (!CheckShaderProgramStatus(programID))
			{
				LOG("Failed to link openGL program");
				return;
			}

			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, fragmentShaderID);
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
		}

		void ShaderProgram::Bind()
		{
			glUseProgram(programID);
			for (int i = 0; i < numAttributes; ++i)
			{
				glEnableVertexAttribArray(i);
			}
		}

		void ShaderProgram::UnBind()
		{
			//Setting to 0 will effectively unbind program in OpenGL
			glUseProgram(0);
			for (int i = 0; i < numAttributes; ++i)
			{
				glDisableVertexAttribArray(i);
			}
		}

		bool ShaderProgram::CheckShaderStatus(GLuint shaderID)
		{
			GLint compileStatus;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
			if (compileStatus != GL_TRUE)
			{
				GLint infoLogLength;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar* buffer = new GLchar[infoLogLength];

				GLsizei bufferSize;
				glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);

				LOG(buffer);

				delete[] buffer;

				glDeleteShader(shaderID);

				return false;
			}
			return true;
		}

		bool ShaderProgram::CheckShaderProgramStatus(GLuint programID)
		{
			GLint linkStatus;
			glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
			if (linkStatus != GL_TRUE)
			{
				GLint infoLogLength;
				glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar* buffer = new GLchar[infoLogLength];

				GLsizei bufferSize;
				glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);

				LOG(buffer);

				delete[] buffer;

				glDeleteProgram(programID);
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);

				return false;
			}

			return true;
		}

		//Class helper function definitions
		std::string ReadShaderSource(const char8* cShaderFilePath, const char8* cTypeOfShader)
		{
			std::ifstream shaderFileInputStream(cShaderFilePath);
			if (!shaderFileInputStream.good())
			{
				LOG("%s Shader File failed to load!\n", cTypeOfShader);
			};

			return std::string(std::istreambuf_iterator<char8>(shaderFileInputStream), std::istreambuf_iterator<char8>());
		}
	}
}