//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "Log.h"
#include "FileSystem.h"
#include "MGUtils.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
Log* g_Log = NULL;
//------------------------------------------------------------------------|
Log::Log(const TCHAR* pPath, const TCHAR* pFilename, bool bSetGlobal)
{
	FileSystem::CreateDirectory(pPath);
	std::wstring sFilePath = std::wstring(pPath) + std::wstring(pFilename);
	m_Stream.open(sFilePath);

	if(bSetGlobal)
		g_Log = this;
}
//------------------------------------------------------------------------|
Log::~Log()
{
	Flush();
	m_Stream.close();

	if(g_Log == this)
		g_Log = NULL;
}
//------------------------------------------------------------------------|
Log& Log::Flush()
{
	if(m_StorageStream.str().length() > 0)
	{
		Write(m_StorageStream.str());
	}
	m_StorageStream.str(L"");
	m_Stream.flush();
	return *this;
}
//------------------------------------------------------------------------|
Log& Log::operator<<(const std::wstring str)
{
	m_StorageStream << str;
	return *this;
}
//------------------------------------------------------------------------|
Log& Log::operator<<(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& (__cdecl *ptr)(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >&))
{
	(*ptr)(m_StorageStream);
	return *this;
}
//------------------------------------------------------------------------|
Log& Log::Write(const wchar_t* str)
{
	std::vector<std::wstring> lines;
	MGUtils::StringSplit(std::wstring(str), std::wstring(L"\n"), lines);

	std::vector<std::wstring>::iterator it = lines.begin();
	std::vector<std::wstring>::iterator itEnd = lines.end();

	std::wstring timestamp = MGUtils::GetTimeStamp();
	std::wstring indent(timestamp.length() + 2, ' ');

	m_Stream << timestamp << "  " << *it << std::endl;
	it++;

	for(; it != itEnd; it++)
	{
		m_Stream << indent << *it << std::endl;
	}

#if _DEBUG
	::OutputDebugStringW(L"DBG: ");
	::OutputDebugStringW( str );
	::OutputDebugStringW( L"\n" );
#endif
	return *this;
}
//------------------------------------------------------------------------|
Log& Log::Write(const std::wstring& str)
{
	return Write(str.c_str());
}
//------------------------------------------------------------------------|
Log& Log::Get()
{
	assert(g_Log && L"No global log created");
	return *g_Log;
}
