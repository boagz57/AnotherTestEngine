#pragma once

/*
	These functions handle all openGL error/status checks and logs (either to console or gl log file)
	the result for 'easy' problem identification
*/

namespace Blz
{
	namespace Graphics
	{
		//Creates new log file each compilation
		bool RestartGLLogFile();

		void LogCurrentGPUCapabilites();
		void LogShaderProgramProperties(GLuint shaderProgramID);
		bool IsProgramValid(GLuint shaderProgramID);

		//Log openGL messages/errors to GL log file
		bool LogToFile(const char8* Message, ...);
	}
}