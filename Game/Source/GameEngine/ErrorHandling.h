#pragma once
#define SPDLOG_DEBUG_ON
#include <SDL.h>
#include <SpdLog\spdlog.h>
#include "ErrorContext.h"

#define ERRASSERT(data, msg, ...) \
	do { Blz::Err::ErrorReport(data, __func__, __FILE__, __LINE__, msg, __VA_ARGS__); } while (0)

namespace Blz
{
	namespace Err
	{
		template<typename ptrType, typename... ArgTypes>
		inline void ErrorReport(ptrType* data, const char* functionName, const char* file, int32 lineNumber, const Blz::string& c_errMessage, ArgTypes... args)
		{
			if (data != nullptr)
			{
				return;
			}
			else
			{
				//Create console object with spdlog
				auto console = spdlog::stdout_color_mt("console");
				//Controls how message is displayed. Different formatters % display different things. https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
				console->set_pattern("  %l: %v");

				ErrorContext::LogContext();
				console->error(c_errMessage.c_str(), args...);
				console->info("In {}() {}: {}", functionName, file, lineNumber);
				SDL_Quit();
				exit(0);
			}
		}
	}
}