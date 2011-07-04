//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include <string>
//------------------------------------------------------------------------|
namespace MG3
{
	class HashedString
	{
	public:
		explicit HashedString(wchar_t const * const pIdentStr)
			: m_cIdentStr(pIdentStr),
			m_ident(HashName(pIdentStr))
		{
		}

		bool operator< (HashedString const& o) const
		{
			bool r = GetIdent() < o.GetIdent();
			return r;
		}
		bool operator== (HashedString const& o) const
		{
			bool r = GetIdent() == o.GetIdent();
			return r;
		}

		static void* HashName(wchar_t const* pIdentStr);
		unsigned long GetIdent() const
		{
			return reinterpret_cast<unsigned long>(m_ident);
		}
		const std::wstring& GetStr() const {return m_cIdentStr;}

	protected:
		
		void*			m_ident;
		std::wstring	m_cIdentStr;
	};		
}