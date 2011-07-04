//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include <fstream>
//------------------------------------------------------------------------|
namespace MG3
{
	class Log
	{
	public:
		Log(const TCHAR* pPath, const TCHAR* pFilename, bool bSetGlobal = false);
		virtual ~Log();

		bool Initialize();

		Log& Flush();

		template <typename T>
		Log& operator << (const T& val)
		{
			m_StorageStream << val;
			return *this;
		}
		Log& operator << (const std::wstring str);
		Log& operator << (std::basic_ostream<wchar_t, std::char_traits<wchar_t> >& (__cdecl *ptr)(std::basic_ostream<wchar_t, std::char_traits<wchar_t> >&));
		Log& operator << (Log& (__cdecl *ptr)(Log& stream))
		{
			(*ptr)(*this);
			return *this;
		}

		Log& Write(const wchar_t* str);
		Log& Write(const std::wstring& str);

		static Log& Get();

	protected:
		std::wofstream m_Stream;
		std::wstringstream m_StorageStream;
		std::wstring m_sLogName;
	};

	inline Log& __cdecl Flush(Log& stream)   { stream.Flush(); return stream; }
}