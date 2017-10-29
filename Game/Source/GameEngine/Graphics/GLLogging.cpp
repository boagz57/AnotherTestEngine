#include <ctime>
#include <stdarg.h>
#include <fstream>
#include <cstdio>
#include <GL/glew.h>
#include "../File.h"
#include "GLLogging.h"

#define GL_LOG_FILE "gl.log"

namespace Blz::Graphics
{
	//Helper functions
	const char* GLTypeToString(GLenum type);

	auto RestartGLLogFile() -> bool
	{
		//Will create a NEW gl.log file, or replace old one, each compilation. 
		//Will use this log file to dump opengl info into to help with debugging
		File glLogFile(GL_LOG_FILE);
		if (!glLogFile.Good())
		{
			LOG("ERROR: could not open GL_LOG_FILE log file %s for writing\n", GL_LOG_FILE);
			return false;
		}

		time_t rawtime = time(&rawtime);
		tm *timeinfo = localtime(&rawtime);

		//Print day and time to top of log file
		glLogFile.Write("%i-%i-%i  %i:%i:%i\n\n", timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_year, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

		glLogFile.Close();

		return true;
	}

	auto LogCurrentGPUCapabilites() -> void
	{
		GLenum params[] =
		{
			GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
			GL_MAX_CUBE_MAP_TEXTURE_SIZE,
			GL_MAX_DRAW_BUFFERS,
			GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
			GL_MAX_TEXTURE_IMAGE_UNITS,
			GL_MAX_TEXTURE_SIZE,
			GL_MAX_VERTEX_ATTRIBS,
			GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
			GL_MAX_VERTEX_UNIFORM_COMPONENTS,
			GL_MAX_VIEWPORT_DIMS,
			GL_STEREO
		};

		const char* names[] =
		{
			"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
			"GL_MAX_CUBE_MAP_TEXTURE_SIZE"
			"GL_MAX_DRAW_BUFFERS",
			"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
			"GL_MAX_TEXTURE_IMAGE_UNITS",
			"GL_MAX_TEXTURE_SIZE",
			"GL_MAX_VERTEX_ATTRIBS",
			"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
			"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
			"GL_MAX_VIEWPORT_DIMS",
			"GL_STEREO"
		};

		//Header
		Graphics::LogToFile("-------------------------------------------------\n");
		LogToFile("GL Context Parameters:\n");
		Graphics::LogToFile("-------------------------------------------------\n\n");

		int32 numberOfGLParametersToLog = 9;
		for (uint16 i = 0; i < numberOfGLParametersToLog; ++i)
		{
			int32 v = 0;
			glGetIntegerv(params[i], &v);
			LogToFile("%s %i\n", names[i], v);
		};
	}

	auto LogShaderProgramProperties(GLuint shaderProgramID) -> void
	{
		//Header
		Graphics::LogToFile("-------------------------------------------------\n");
		Graphics::LogToFile("Shader program %i\n", shaderProgramID);
		Graphics::LogToFile("-------------------------------------------------\n\n");

		int32 result = -1;
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
		Graphics::LogToFile("GL_LINK_STATUS = %s\n", (result == GL_TRUE) ? "SUCCESS" : "FAILURE");

		glGetProgramiv(shaderProgramID, GL_ATTACHED_SHADERS, &result);
		Graphics::LogToFile("GL_ATTACHED_SHADERS = %i\n", result);

		glGetProgramiv(shaderProgramID, GL_ACTIVE_ATTRIBUTES, &result);
		Graphics::LogToFile("GL_ACTIVE_ATTRIBUTES = %i\n", result);

		//Will log all current active attributes for program/shader
		for (GLuint i = 0; i < (GLuint)result; ++i)
		{
			char name[64];
			int32 maxLength = 64;
			int32 actualLength = 0;
			int32 size = 0;
			GLenum type;

			glGetActiveAttrib(shaderProgramID, i, maxLength, &actualLength, &size, &type, name);
			if (size > 1)
			{
				//Sometimes an attribute will contain an array of other attributes for which this
				//loop will catch and print all contained variables
				for (int j = 0; j < size; j++)
				{
					char longName[64];
					sprintf(longName, "%s[%i]", name, j);
					int32 location = glGetAttribLocation(shaderProgramID, longName);
					Graphics::LogToFile(" - %i) type:%s name:%s location: %i\n", i, GLTypeToString(type), name, location);
				}
			}
			else
			{
				//Just print single attribute information
				int32 location = glGetAttribLocation(shaderProgramID, name);
				Graphics::LogToFile(" - %i) type:%s name:%s location %i\n", i, GLTypeToString(type), name, location);
			}
		}

		glGetProgramiv(shaderProgramID, GL_ACTIVE_UNIFORMS, &result);
		LogToFile("GL_ACTIVE_UNIFORMS = %i\n", result);

		//Will log all current active attributes for program/shader
		for (GLuint i = 0; i < (GLuint)result; ++i)
		{
			char name[64];
			int32 maxLength = 64;
			int32 actualLength = 0;
			int32 size = 0;
			GLenum type;

			glGetActiveUniform(shaderProgramID, i, maxLength, &actualLength, &size, &type, name);
			if (size > 1)
			{
				//In case a uniform contains an array of other variables/uniforms
				for (int j = 0; j < size; j++)
				{
					char longName[64];
					sprintf(longName, "%s[%i]", name, j);
					int32 location = glGetUniformLocation(shaderProgramID, longName);
					Graphics::LogToFile(" - %i) type:%s name:%s location: %i\n", i, GLTypeToString(type), longName, location);
				}
			}
			else
			{
				//Just print single uniform variable 
				int32 location = glGetUniformLocation(shaderProgramID, name);
				Graphics::LogToFile(" - %i) type:%s name:%s location %i\n", i, GLTypeToString(type), name, location);
			}
		}

		int32 maxLength = 2048;
		int32 actualLength = 0;
		char log[2048];
		glGetProgramInfoLog(shaderProgramID, maxLength, &actualLength, log);
		Graphics::LogToFile("Program info log for GL index %u:\n%s", shaderProgramID, log);
	}

	auto IsProgramValid(GLuint shaderProgramID) -> bool
	{
		glValidateProgram(shaderProgramID);

		int32 result = -1;
		glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &result);
		LOG("program %i GL_VALIDATE_STATUS = %s\n", shaderProgramID, (result == GL_TRUE) ? "VALID" : "INVALID!");

		if (result != GL_TRUE)
		{
			int32 maxLength = 2048;
			int32 actualLength = 0;
			char log[2048];
			glGetProgramInfoLog(shaderProgramID, maxLength, &actualLength, log);
			Graphics::LogToFile("Program info log for GL index %u:\n%s", shaderProgramID, log);

			return false;
		}

		return true;
	}

	auto LogToFile(const char* c_Message, ...) -> bool
	{
		File glLogFile;
		glLogFile.Open(GL_LOG_FILE, "a");

		//Captures ellipses arguments
		va_list argptr;
		va_start(argptr, c_Message);//Initializes the va_list

		if (!glLogFile.Good())
		{
			LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
			return false;
		}

		glLogFile.Write(c_Message, argptr);

		//cleans up argptr va_list
		va_end(argptr);

		glLogFile.Close();

		return true;
	}

	//Helper function definitions

	//Used to make GL types printable and readable in the log file
	auto GLTypeToString(GLenum type) -> const char*
	{
		switch (type)
		{
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2D";
		case GL_SAMPLER_3D: return "sampler3D";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";

		default: break;
		}

		return "other";
	}
}