//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include <string>
//------------------------------------------------------------------------|
namespace MG3
{
	class MGUtils
	{
	public:
		MGUtils();
		virtual ~MGUtils();

		static std::wstring GetTimeStamp();
		static void StringSplit(std::wstring& str, std::wstring& delim, std::vector<std::wstring>& result);

	protected:
		
	};
}