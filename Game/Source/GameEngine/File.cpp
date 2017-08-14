#include <stdarg.h>
#include <stdio.h>
#include "File.h"

//TODO: change implementation to more secure and portable c++ file handling

namespace Blz 
{ 
	File::File()
	{
	}

	File::File(char* p_FileName) :
		p_OutputFile(p_OutputFile = fopen(p_FileName, "w")),
		cp_Filename(p_FileName)
	{
	}

	File::~File()
	{
		fclose(p_OutputFile);
	}

	void File::Open(const char* c_FileName, const char* mode)
	{
		p_OutputFile = fopen(c_FileName, mode);
	}

	void File::Close()
	{
		fclose(p_OutputFile);
	}

	bool File::Good()
	{
		if (!p_OutputFile)
		{
			LOG("ERROR: could not open %s file for appending\n", this->cp_Filename);
			return false;
		}

		return true;
	}

	void File::Write(const char * cp_Message, ...)
	{
		//Believe this captures the ellipsis parameter in your function
		va_list argptr;
		va_start(argptr, cp_Message);//Initializes the va_list

		vfprintf(p_OutputFile, cp_Message, argptr);

		va_end(argptr);//Cleans up the va_list
	}

	void File::Write(const char * cp_Message, va_list argptr)
	{
		vfprintf(p_OutputFile, cp_Message, argptr);

		va_end(argptr);
	}
}
