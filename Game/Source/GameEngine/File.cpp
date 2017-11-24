#include <stdarg.h>
#include <stdio.h>
#include "File.h"

//TODO: change implementation to more secure and portable c++ file handling

namespace Blz 
{ 
	File::File(char* p_FileName) :
		p_OutputFile(p_OutputFile = fopen(p_FileName, "w")),
		cp_Filename(p_FileName)
	{
	}

	File::~File()
	{
		fclose(p_OutputFile);
	}

	auto File::Open(const char* c_FileName, const char* mode) -> void
	{
		p_OutputFile = fopen(c_FileName, mode);
	}

	auto File::Close() -> void
	{
		fclose(p_OutputFile);
	}

	auto File::Good() -> bool
	{
		if (!p_OutputFile)
		{
			CONSOLE("ERROR: could not open %s file for appending\n", this->cp_Filename);
			return false;
		}

		return true;
	}

	auto File::Write(const char * cp_Message, ...) -> void
	{
		//Believe this captures the ellipsis parameter in your function
		va_list argptr;
		va_start(argptr, cp_Message);//Initializes the va_list

		vfprintf(p_OutputFile, cp_Message, argptr);

		va_end(argptr);//Cleans up the va_list
	}

	auto File::Write(const char * cp_Message, va_list argptr) -> void
	{
		vfprintf(p_OutputFile, cp_Message, argptr);

		va_end(argptr);
	}
}
