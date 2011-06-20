#pragma once

#include "MG3.h"

namespace MG3
{
	class Window
	{
	public:
		Window();
		virtual ~Window();

		virtual void Initialize() = 0;
		virtual void Exit() = 0;
		virtual void Paint() = 0;

		HWND GetHandle();

		void SetWidth(int width);
		void SetHeight(int height);

		void SetTitle(std::wstring& title);
		std::wstring GetTitle();

	protected:

		void UpdateWindowState();

		HWND			m_hWnd;
		std::wstring	m_sTitle;

		int				m_iWidth;
		int				m_iHeight;
		int				m_iLeft;
		int				m_iTop;

		DWORD			m_dStyle;
	};
}