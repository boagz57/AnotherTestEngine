#pragma once

namespace Blz
{
	class File
	{
	public:
		File() = default;
		//Opens or creates(if not already created) a file for writing
		File(char* fileName);
		~File();

		void Open(const char* fileName, const char* mode);
		void Close();
		bool Good();

		void Write(const char* message, ...);

		//So you can pass around variable arguments from another function to this one
		void Write(const char* message, va_list);

	private:
		const char* cp_Filename = nullptr;
		FILE* p_OutputFile = nullptr;
	};
}
