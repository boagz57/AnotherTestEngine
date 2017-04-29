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

		void Close();
		void Open(const char8* fileName, const char8* mode);
		bool Good();

		void Write(const char8* message, ...);

	private:
		const char8* cp_Filename;
		FILE* p_OutputFile;
	};
}
