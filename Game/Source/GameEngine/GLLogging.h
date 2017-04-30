#pragma once

namespace Blz
{
	namespace GLLogging
	{
		//Creates new log file each compilation
		bool RestartGLLogFile();

		void LogCurrentGPUCapabilites();

		//Log openGL messages/errors to GL log file
		bool LogToFile(const char8* Message, ...);
	}
}