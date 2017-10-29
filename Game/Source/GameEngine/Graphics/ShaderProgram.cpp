#include <fstream>
#include <GL\glew.h>
#include "ShaderProgram.h"

namespace Blz::Graphics
{
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(programID);
	}

	auto ShaderProgram::Init(Blz::string vertexShaderFilePath, Blz::string fragmentShaderFilePath) -> void
	{
		vertexShaderFile = vertexShaderFilePath;
		fragmentShaderFile = fragmentShaderFilePath;
		programID = glCreateProgram();
	}

	auto ShaderProgram::Compile() -> void
	{
		auto ReadShaderSourceFile = [](const char* c_ShaderFilePath, const char* c_TypeOfShader) -> Blz::string
		{
			std::ifstream shaderFileInputStream(c_ShaderFilePath);
			if (!shaderFileInputStream.good())
			{
				LOG("%s Shader File failed to load!\n", c_TypeOfShader);
			};

			return Blz::string(std::istreambuf_iterator<char>(shaderFileInputStream), std::istreambuf_iterator<char>());
		};

		//Create GL Shaders
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* cAdapter[1];

		//Add source or text file to shader object
		Blz::string temp = ReadShaderSourceFile(vertexShaderFile.c_str(), "Vertex").c_str();
		cAdapter[0] = temp.c_str();
		glShaderSource(vertexShaderID, 1, cAdapter, 0);

		temp = ReadShaderSourceFile(fragmentShaderFile.c_str(), "Fragment").c_str();
		cAdapter[0] = temp.c_str();
		glShaderSource(fragmentShaderID, 1, cAdapter, 0);

		glCompileShader(vertexShaderID);
		glCompileShader(fragmentShaderID);

		if (!CheckShaderStatus(vertexShaderID) || !CheckShaderStatus(fragmentShaderID))
			return;
	}

	auto ShaderProgram::AddAttribute(Blz::string attributeName) -> void
	{
		glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
	}

	auto ShaderProgram::GetUniformLocation(Blz::string uniformNameFromShader) -> GLuint
	{
		GLuint location = glGetUniformLocation(programID, uniformNameFromShader.c_str());
		return location;
	}

	auto ShaderProgram::Link() -> void
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

	auto ShaderProgram::Bind() -> void
	{
		glUseProgram(programID);
		for (int i = 0; i < numAttributes; ++i)
		{
			glEnableVertexAttribArray(i);
		};
	}

	auto ShaderProgram::UnBind() -> void
	{
		//Setting to 0 will effectively unbind program in OpenGL
		glUseProgram(0);
		for (int i = 0; i < numAttributes; ++i)
		{
			glDisableVertexAttribArray(i);
		}
	}

	auto ShaderProgram::CheckShaderStatus(GLuint shaderID) -> bool
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

	auto ShaderProgram::CheckShaderProgramStatus(GLuint programID) -> bool
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
}