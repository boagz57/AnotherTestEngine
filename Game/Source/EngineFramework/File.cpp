#include "File.h"
#include <stdarg.h>
#include <stdio.h>

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

	void File::Open(const char8* cFileName, const char8* mode)
	{
		p_OutputFile = fopen(cFileName, mode);
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

	void File::Write(const char8 * cpMessage, ...)
	{
		//Believe this captures the ellipsis parameter in your function
		va_list argptr;
		va_start(argptr, cpMessage);//Initializes the va_list

		vfprintf(p_OutputFile, cpMessage, argptr);

		va_end(argptr);//Cleans up the va_list
	}
}
