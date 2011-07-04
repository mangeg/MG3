//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include <string>
//------------------------------------------------------------------------|
namespace MG3
{
	class FileSystem
	{
	public:
		FileSystem();
		virtual ~FileSystem();

		static std::wstring GetAppDataFolder(std::wstring sCompanyName = L"MG", std::wstring AppName = L"MG3");
		static bool FolderExists(const TCHAR* pPath);
		static bool CreateDirectory(const TCHAR* pPath);
		static std::wstring GetWorkingDirectory();
		static std::wstring GetDirectory(std::wstring const& str);
		static std::wstring GetFileName(std::wstring const& str);
		static std::wstring ChangeFileExtention(std::wstring const& file, std::wstring const& newFileEnding);
		static std::wstring GetFileExtention(std::wstring const& file);
	};
}