//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "FileSystem.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
FileSystem::FileSystem()
{
}
//------------------------------------------------------------------------|
FileSystem::~FileSystem()
{
}
//------------------------------------------------------------------------|
std::wstring FileSystem::GetAppDataFolder(std::wstring sCompanyName, std::wstring AppName)
{
	
	wchar_t buffer[MAX_PATH];

	HRESULT hr = SHGetFolderPath(0,
		CSIDL_LOCAL_APPDATA,
		0,
		SHGFP_TYPE_CURRENT,
		buffer);

	std::wstringstream s;
	s << buffer << "\\" << sCompanyName << "\\" << AppName << "\\";

	return s.str();
}
//------------------------------------------------------------------------|
bool FileSystem::FolderExists(const TCHAR* pPath)
{
	if(0xffffffff == GetFileAttributes(pPath))
	{
		return false;
	}
	return true;
}
//------------------------------------------------------------------------|
bool FileSystem::CreateDirectory(const TCHAR* pPath)
{
	if (FolderExists(pPath))
		return true;

	int res = SHCreateDirectoryEx(NULL, pPath, NULL);

	return true;
}
//------------------------------------------------------------------------|
std::wstring FileSystem::GetWorkingDirectory()
{
	TCHAR buf[MAX_PATH] = {0};
	GetModuleFileName(NULL, buf, MAX_PATH);	

	return GetDirectory(buf);
}
//------------------------------------------------------------------------|
std::wstring FileSystem::GetDirectory(std::wstring const& str)
{
	int last = str.find_last_of(_T("\\"));
	if(last == str.size() - 1)
	{
		return str;
	}

	return str.substr(0, last + 1);
}
//------------------------------------------------------------------------|
std::wstring FileSystem::GetFileName(std::wstring const& str)
{
	int last = str.find_last_of(_T("."));
	int lastBack = str.find_last_of(_T("\\"));

	// File path have *.* format
	if(last != -1)
	{		
		if(lastBack != -1)
		{
			return str.substr(lastBack + 1);
		}
		else
		{
			return str;
		}
	}

	// Filename may have *\* format
	return str;
}
//------------------------------------------------------------------------|
std::wstring FileSystem::ChangeFileExtention(std::wstring const& file, 
	std::wstring const& newFileEnding)
{
	int last = file.find_last_of(_T("."));

	if(last != -1)
	{
		return file.substr(0, last + 1) + newFileEnding;
	}
	else
	{
		return file + L"." + newFileEnding;
	}
}
//------------------------------------------------------------------------|
std::wstring FileSystem::GetFileExtention(std::wstring const& file)	
{
	int last = file.find_last_of(_T("."));
	if(last != std::string::npos)
	{
		return file.substr(last);
	}
	return L"";
}