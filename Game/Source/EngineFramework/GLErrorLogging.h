#pragma once

namespace Blz
{
	namespace OpenGL
	{
		bool RestartGLLogFile();

		//Log openGL messages/errors to GL log file
		bool LogToFile(const char8* cMessage);
		bool LogToFile(const char8* cMessage, const char8* cStringToInsertInMessage);
		bool LogToFile(const char8* cMessage, const char8* cStringToInsertInMessage, int numberToInsertInMessage);
		bool LogToFile(const char8* cMessage, int numberToInsertInMessage);

		//Log openGL messages/errors to BOTH log file and console
		bool LogToFileAndConsole(const char8* cMessage);
		bool LogToFileAndConsole(const char8* cMessage, const char8* cString);
		bool LogToFileAndConsole(const char8* cMessage, const char8* cString, int number);
		bool LogToFileAndConsole(const char8* cMessage, int number);
	}
}