#include <ctime>
#include <stdarg.h>
#include <fstream>
#include "GL/glew.h"
#include "File.h"
#include "GLLogging.h"

#define GL_LOG_FILE "gl.log"

namespace Blz
{
	namespace GLLogging
	{
		bool RestartGLLogFile()
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

		void LogCurrentGPUCapabilites()
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

			LogToFile("GL Context Parameters:\n\n");

			int32 numberOfGLParametersToLog = 9;
			for (uint16 i = 0; i < numberOfGLParametersToLog; ++i)
			{
				int32 v = 0;
				glGetIntegerv(params[i], &v);
				LogToFile("%s %i\n", names[i], v);
			};

			LogToFile("-------------------------------------------------\n\n");
		}

		bool LogToFile(const char8* c_Message, ...) 
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
	}
}