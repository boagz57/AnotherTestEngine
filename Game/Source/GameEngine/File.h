#pragma once

namespace Blz
{
	class File
	{
	public:
		File();
		//Opens or creates(if not already created) a file for writing
		File(char8* fileName);
		~File();

		void Open(const char8* fileName, const char8* mode);
		void Close();
		bool Good();

		void Write(const char8* message, ...);

		//So you can pass around variable arguments from another function to this one
		void Write(const char8* message, va_list);

	private:
		const char8* cp_Filename;
		FILE* p_OutputFile;
	};
}
