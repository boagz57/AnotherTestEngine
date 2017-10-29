#pragma once

/*
	These functions handle all openGL error/status checks and logs (either to console or gl log file)
	the result for 'easy' problem identification
*/

namespace Blz::Graphics
{
	//Creates new log file each compilation
	auto RestartGLLogFile() -> bool;

	auto LogCurrentGPUCapabilites() -> void;
	auto LogShaderProgramProperties(GLuint shaderProgramID) -> void;
	auto IsProgramValid(GLuint shaderProgramID) -> bool;

	//Log openGL messages/errors to GL log file
	auto LogToFile(const char* Message, ...) -> bool;
}