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

		void LogParameters()
		{
			GLenum params[] =
			{
				GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
				GL_MAX_CUBE_MAP_TEXTURE_SIZE,
			};

			const char* names[] =
			{
				"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
				"GL_MAX_CUBE_MAP_TEXTURE_SIZE"
			};

			LogToFile("GL Context Parameters:\n");

			for (uint16 i = 0; i < 1; ++i)
			{
				GLint v = 0;
				glGetIntegerv(params[i], &v);
				LogToFile("%s %i", names[i], v);
			}

			LogToFile("-------------------------------------------------\n");
		}

		bool LogToFile(const char8* c_Message)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(c_Message);

			glLogFile.Close();

			return true;
		}

		bool LogToFile(const char8* c_Message, const char8* c_String)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(c_Message, c_String);

			glLogFile.Close();

			return true;
		}

		bool LogToFile(const char8 * c_Message, const char8* c_StringToInsertInMessage, int numberToInsertInMessage)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(c_Message, c_StringToInsertInMessage, numberToInsertInMessage);

			glLogFile.Close();

			return true;
		}

		bool LogToFile(const char8 * c_Message, int numberToInsertInMessage)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(c_Message, numberToInsertInMessage);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8* c_Message)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(c_Message);
			//Prints to console
			LOG(c_Message);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8 * c_Message, const char8 * c_String)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(c_Message, c_String);
			//Prints to console
			LOG(c_Message, c_String);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8 * c_Message, const char8 * c_String, int number)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(c_Message, c_String, number);
			//Prints to console
			LOG(c_Message, c_String, number);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8 * c_Message, int number)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(c_Message, number);
			//Prints to console
			LOG(c_Message, number);

			glLogFile.Close();

			return true;;
		}
	}
}