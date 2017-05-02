#pragma once

namespace Blz
{
	namespace OpenGL
	{
		//Creates new log file each compilation
		bool RestartGLLogFile();

		void LogCurrentGPUCapabilites();
		void LogTest(GLuint shaderProgram);

		//Log openGL messages/errors to GL log file
		bool LogToFile(const char8* Message, ...);
	}
}