#pragma once
#include <SpdLog\spdlog.h>
#include <boost/assert.hpp>
#include <assert.h>

namespace Blz
{
	namespace Err
	{
		class ErrContext
		{
		public:
			ErrContext(const char* c_ErrorContextDescription, const char* c_ErrorContexDataDescription = "");
			~ErrContext();
			ErrContext(const ErrContext& copy) = delete;
			void operator=(const ErrContext& copy) = delete;

			static auto LogContext() -> void;
		};

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
			SDL_Quit();
			exit(0);
		}
	}
}

#if (DEBUG)
#define ERRASSERT(condition, msg, ...) \
		do { if (!(condition)) Blz::Err::ErrorReport(#condition, __func__, __FILE__, __LINE__, msg, __VA_ARGS__); } while (0)

#define ERRCONTEXT(context, data) \
		Blz::Err::ErrContext ec(context, data);

#else
#define ERR_ASSERT(condition, msg, ...) (void(0))
#define ERR_CONTEXT(context, data) (void(0))

#endif

#if (DEBUG)
#define BLZ_RUNTIME_ASSERT \
		BOOST_ASSERT_MSG 

#define BLZ_COMPILETIME_ASSERT(expr, msg) \
		static_assert(expr, msg) 

#else
#define RUNTIME_ASSERT (void(0))
#define COMPILETIME_ASSERT(expr, msg) (void(0))

#endif
