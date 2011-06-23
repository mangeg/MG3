#pragma once

#include "MG3.h"

namespace MG3
{
	class ScriptConsole
	{
	public:
		static LRESULT WINAPI MsgProc(HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK SubclassInputEditProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		
		static void Init(HINSTANCE hInstance);
		static HWND ShowConsole();
		static void HideConsole();
		static void Toggle();
		static void Write(const char *pString);
		static HWND GetHandle();

		static bool IsReady() {return m_hWnd != NULL;}

	private:
		ScriptConsole();
		~ScriptConsole();

		void Initialize(HINSTANCE hInstance);
		void ResizeControls();
		void AdjustScrollBar();
		void Paint(HDC hDC);

		static volatile bool m_bIsActive;
		static volatile bool m_bIsShown;
		static volatile HWND m_hWnd;
		static volatile HWND m_hEditControl;
		static wchar_t m_CommandBufferW[4096];

		std::list<std::string> m_stringList;

		static HINSTANCE m_hInstance;

		int m_iScrollPos;
		int m_iTextAreaHeight;
	};

	extern ScriptConsole *gScriptConsole;
}