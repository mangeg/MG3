#pragma once

#include "StdAfx.h"

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

		void SetTitle(std::wstring& title);	
		void SetWidth(int width);
		void SetHeight(int height);			

		std::wstring GetTitle();
		int GetWidth();
		int GetHeight();

		void SetSwapChain(int iSwapChain);
		int GetSwapChain();

	protected:

		void _UpdateWindowState();

		HWND			m_hWnd;
		std::wstring	m_sTitle;

		int				m_iWidth;
		int				m_iHeight;
		int				m_iLeft;
		int				m_iTop;

		int				m_iSwapChain;

		DWORD			m_dStyle;
	};
}