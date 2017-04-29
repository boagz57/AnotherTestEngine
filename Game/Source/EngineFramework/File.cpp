#include "File.h"
#include <stdarg.h>
#include <stdio.h>

//TODO: change implementation to more secure and portable c++ file handling

namespace Blz 
{ 
	File::File()
	{
	}

	File::File(char8* p_FileName) :
		p_OutputFile(p_OutputFile = fopen(p_FileName, "w")),
		cp_Filename(p_FileName)
	{
	}

	File::~File()
	{
		fclose(p_OutputFile);
	}

	void File::Close()
	{
		fclose(p_OutputFile);
	}

	void File::Open(const char8* c_FileName, const char8* mode)
	{
		p_OutputFile = fopen(c_FileName, mode);
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

	void File::Write(const char8 * cp_Message, ...)
	{
		//Believe this captures the ellipsis parameter in your function
		va_list argptr;
		va_start(argptr, cp_Message);//Initializes the va_list

		vfprintf(p_OutputFile, cp_Message, argptr);

		va_end(argptr);//Cleans up the va_list
	}
}
