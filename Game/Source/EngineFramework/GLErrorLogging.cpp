#include <ctime>
#include <stdarg.h>
#include <fstream>
#include "File.h"
#include "GLErrorLogging.h"

#define GL_LOG_FILE "gl.log"

namespace Blz
{
	namespace OpenGL
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

		bool LogToFile(const char8* cMessage)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(cMessage);

			glLogFile.Close();

			return true;
		}

		bool LogToFile(const char8* cMessage, const char8* cString)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(cMessage, cString);

			glLogFile.Close();

			return true;
		}

		bool LogToFile(const char8 * cMessage, const char8* cStringToInsertInMessage, int numberToInsertInMessage)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(cMessage, cStringToInsertInMessage, numberToInsertInMessage);

			glLogFile.Close();

			return true;
		}

		bool LogToFile(const char8 * cMessage, int numberToInsertInMessage)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			glLogFile.Write(cMessage, numberToInsertInMessage);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8* cMessage)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(cMessage);
			//Prints to console
			LOG(cMessage);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8 * cMessage, const char8 * cString)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(cMessage, cString);
			//Prints to console
			LOG(cMessage, cString);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8 * cMessage, const char8 * cString, int number)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(cMessage, cString, number);
			//Prints to console
			LOG(cMessage, cString, number);

			glLogFile.Close();

			return true;
		}

		bool LogToFileAndConsole(const char8 * cMessage, int number)
		{
			File glLogFile;
			glLogFile.Open(GL_LOG_FILE, "a");

			if (!glLogFile.Good())
			{
				LOG("ERROR: could not open %s file for appending\n", GL_LOG_FILE);
				return false;
			}

			//Prints to log file
			glLogFile.Write(cMessage, number);
			//Prints to console
			LOG(cMessage, number);

			glLogFile.Close();

			return true;;
		}
	}
}