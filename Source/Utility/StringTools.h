#pragma once

#include "MG3.h"

namespace MG3
{
	class StringTools
	{
	public:
		static std::string ToAscii(std::wstring& txt);
		static std::wstring ToUnicode(std::string& txt);

	private:
		StringTools();
	};
}