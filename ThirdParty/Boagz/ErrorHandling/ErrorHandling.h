#pragma once
#include <SpdLog\spdlog.h>
#include <assert.h>
#include <boost/assert.hpp>
#include "ErrorContext.h"

#if BGZ_ERRHANDLING_ON
	#define BGZ_ERRCTXT1(errorDescription) \
		Bgz::Err::ErrContext ec(errorDescription);

	#define BGZ_ERRCTXT2(errorDescription, errorData) \
		Bgz::Err::ErrContext ec(errorDescription, errorData);

	#define BGZ_ERRASSERT(condition, msg, ...) \
		do { if (!(condition)) Bgz::Err::ErrorReport(#condition, __func__, __FILE__, __LINE__, msg, __VA_ARGS__); } while (0)

	#define BGZ_RUNTIME_ASSERT \
		BOOST_ASSERT_MSG 

	#define BGZ_COMPILETIME_ASSERT(expr, msg) \
		static_assert(expr, msg) 

#else
	#define BGZ_ERRCTXT1(errorDescription) __noop
	#define BGZ_ERRCTXT2(errorDescription, errorData) __noop
	#define BGZ_ERRASSERT(condition, msg, ...) __noop
	#define BGZ_RUNTIME_ASSERT __noop
	#define BGZ_COMPILETIME_ASSERT(expr, msg) __noop

#endif

namespace Bgz
{
	namespace Err
	{
		template<typename... ArgTypes>
		inline auto ErrorReport(const char* condition, const char* functionName, const char* file, int32 lineNumber, const Blz::string& c_errMessage, ArgTypes... args) -> void
		{
			//Create console object with spdlog
			auto console = spdlog::stdout_color_mt("console");
			//Controls how message is displayed. Different formatters % display different things. https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
			console->set_pattern("  %l: %v");

			//Combinging both 'condition' message and 'c_errMessage' first to keep everything on one line in console
			Blz::string combinedErrMessages("Assertion failed: " + Blz::string(condition) + " \n         " + c_errMessage);

			ErrContext::LogContext();

			console->error(combinedErrMessages.c_str(), args...);
			console->info("In function {}() \n        {}: {}", functionName, file, lineNumber);
			exit(0);
		}
	}
}