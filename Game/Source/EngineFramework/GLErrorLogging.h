#pragma once

namespace Blz
{
	namespace OpenGL
	{
		bool RestartGLLogFile();

		//Log openGL messages/errors to GL log file
		bool LogToFile(const char8* Message);
		bool LogToFile(const char8* Message, const char8* StringToInsertInMessage);
		bool LogToFile(const char8* Message, const char8* StringToInsertInMessage, int numberToInsertInMessage);
		bool LogToFile(const char8* Message, int numberToInsertInMessage);

		//Log openGL messages/errors to BOTH log file and console
		bool LogToFileAndConsole(const char8* Message);
		bool LogToFileAndConsole(const char8* Message, const char8* StringToInsertInMessage);
		bool LogToFileAndConsole(const char8* Message, const char8* StringToInsertInMessage, int numberToInsertInMessage);
		bool LogToFileAndConsole(const char8* Message, int numberToInsertInMessage);
	}
}