//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MGUtils.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MGUtils::MGUtils()
{
}
//------------------------------------------------------------------------|
MGUtils::~MGUtils()
{
}
//------------------------------------------------------------------------|
std::wstring MGUtils::GetTimeStamp()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	wchar_t timestamp[200];
	_snwprintf_s(timestamp, _TRUNCATE, L"%04u-%02u-%02u %02u:%02u:%02u.%-.3u", 
		t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

	return std::wstring(timestamp);
}
//------------------------------------------------------------------------|
void MGUtils::StringSplit(std::wstring& str, std::wstring& delim, std::vector<std::wstring>& result)
{
	int start = 0;
	int end = str.find_first_of(L"\n");
	if(end != -1)
	{
		while(end != -1)
		{
			result.push_back(str.substr(start, end - start));
			start = end + 1;
			end = str.find_first_of(L"\n", start);
			if(end == -1)
			{
				result.push_back(str.substr(start));
			}
		}
	}
	else
	{
		result.push_back(str.substr(start));
	}
}