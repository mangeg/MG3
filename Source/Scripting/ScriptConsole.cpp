#include "StdAfx.h"
#include "ScriptConsole.h"
#include "StringTools.h"

using namespace MG3;

ScriptConsole* MG3::gScriptConsole = NULL;

volatile bool ScriptConsole::m_bIsShown = false;
volatile bool ScriptConsole::m_bIsActive = true;
HINSTANCE ScriptConsole::m_hInstance = NULL;
volatile HWND ScriptConsole::m_hWnd = NULL;
volatile HWND ScriptConsole::m_hEditControl = NULL;

wchar_t ScriptConsole::m_CommandBufferW[4096];

WNDPROC lpfnInputEdit;

void ScriptConsole::Init(HINSTANCE hInstance)
{	
	m_hInstance = hInstance;	
}

HWND ScriptConsole::ShowConsole()
{

	if(!gScriptConsole)
	{
		gScriptConsole = new ScriptConsole();
	}

	if(!m_hWnd)
	{
		gScriptConsole->Initialize(m_hInstance);
	}

	m_bIsShown = true;

	return m_hWnd;
}

void ScriptConsole::HideConsole()
{
	if(gScriptConsole)
	{
		SAFE_DELETE(gScriptConsole);
	}	

	m_bIsShown = false;
}

void ScriptConsole::Toggle()
{
	if(m_bIsShown)
		HideConsole();
	else
		ShowConsole();
}

ScriptConsole::ScriptConsole()
{
	m_hWnd = NULL;
	ZeroMemory(m_CommandBufferW, sizeof(wchar_t) * 4096);	
}

ScriptConsole::~ScriptConsole()
{
	if(m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}

void ScriptConsole::AdjustScrollBar()
{
	if(gScriptConsole && m_hWnd)
	{
		SCROLLINFO si;
		ZeroMemory(&si, sizeof(SCROLLINFO));

		si.cbSize	= sizeof(SCROLLINFO);
		si.fMask	= SIF_RANGE | SIF_PAGE | SIF_POS;
		si.nMin		= 0;
		si.nMax		= m_stringList.size();
		si.nPage	= m_iTextAreaHeight;
		si.nPos		= m_stringList.size() - m_iScrollPos;
		SetScrollInfo(m_hWnd, SB_VERT, &si, TRUE);
	}
}

void ScriptConsole::ResizeControls()
{
	RECT r;

	GetClientRect(m_hWnd, &r);
	m_iTextAreaHeight = (r.bottom - r.top) / 16;

	SetWindowPos(m_hEditControl, HWND_TOP, r.left + 2, r.bottom - 18, r.right - r.left - 4, 16, SWP_NOZORDER);

	AdjustScrollBar();
	InvalidateRect(m_hWnd, NULL, TRUE);
}

void ScriptConsole::Paint(HDC hDC)
{
	SetTextColor(hDC, RGB(64, 255, 64));
	SetBkColor(hDC, RGB(0, 0, 0));

	RECT r;

	GetClientRect(m_hWnd, &r);

	int x = 2;
	int y = r.bottom - 40;

	std::list<std::string>::iterator it = m_stringList.begin();
	int skip = m_iScrollPos;

	while(skip)
	{
		++it;
		--skip;
	}

	while(it != m_stringList.end())
	{
		TextOut(hDC, x, y, StringTools::ToUnicode(std::string(*it)).c_str(), strlen((*it).c_str()));
		y -= 16;
		++it;
	}
}

LRESULT WINAPI ScriptConsole::MsgProc(HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (uMsg)
	{
	case WM_ACTIVATEAPP:
		m_bIsActive = (wParam != 0);
		return 0L;

	case WM_ACTIVATE:
		// Pause if minimized or not the top window
		m_bIsActive = (wParam == WA_ACTIVE) || (wParam == WA_CLICKACTIVE);
		return 0L;

	case WM_DESTROY:
		m_bIsShown = false;
		m_bIsActive = false;
		m_hWnd = NULL;
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		gScriptConsole->Paint(hdc);
		EndPaint(hWnd, &ps);
		break;

	case WM_CHAR:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
		break;

	case WM_RBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_COMMAND:
		break;

	case WM_SIZING:
	case WM_SIZE:
		gScriptConsole->ResizeControls();
		break;

	case WM_SETCURSOR:
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		ShowCursor(TRUE);
		break;

	case WM_VSCROLL: 
		switch(wParam & 0xFFFF)//LOWORD (wParam)) 
		{ 
			// User clicked the shaft above the scroll box. 

		case SB_PAGEUP: 
			//g_Console->m_ScrollyPos = std::min((int) (g_Console->m_ScrollyPos+g_Console->m_textAreaHeight), (int) (g_Console->m_stringList.size() - g_Console->m_textAreaHeight)+1);
			//yInc = min(-1, -yClient / yChar); 
			break; 

			// User clicked the shaft below the scroll box. 

		case SB_PAGEDOWN: 
			// yInc = max(1, yClient / yChar); 
			break; 

			// User clicked the top arrow. 

		case SB_LINEUP: 
			//g_Console->m_ScrollyPos = std::min(g_Console->m_ScrollyPos+1, (int) (g_Console->m_stringList.size() - g_Console->m_textAreaHeight)+1);
			break; 

			// User clicked the bottom arrow. 

		case SB_LINEDOWN: 
			//yInc = 1; 
			//g_Console->m_ScrollyPos = std::max(g_Console->m_ScrollyPos-1, 0);
			break; 

			// User dragged the scroll box. 

		case SB_THUMBTRACK: 
			//yInc = HIWORD(wParam) - yPos; 
			break; 

		default: 
			//yInc = 0;
			break;

		} 

		InvalidateRect(m_hWnd, NULL, TRUE);

		break;

	case WM_USER:
		// command ready from edit control
		// string should be in m_CommandBuffer
		std::string command = StringTools::ToAscii( std::wstring( m_CommandBufferW ) );
		Write(command.c_str());
		// clear buffer when done processing
		memset(m_CommandBufferW, 0, 4096*sizeof(wchar_t));
		break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

void ScriptConsole::Write(const char *pString)
{
	if(gScriptConsole && m_hWnd)
	{
		char *buf = new char[strlen(pString)+1];
		int index = 0;
		for (int i = 0; i < (int)strlen(pString); i++)
		{
			if(pString[i] != 10)
			{
				buf[index++] = pString[i];
			}
			else
			{
				buf[index] = 0;
				gScriptConsole->m_stringList.push_front(buf);
				index = 0;
			}
		}

		if(index > 0)
		{
			buf[index] = 0;
			gScriptConsole->m_stringList.push_front(buf);
		}

		InvalidateRect(m_hWnd, NULL, TRUE);
		delete buf;
	}

	gScriptConsole->AdjustScrollBar();
}

LRESULT CALLBACK ScriptConsole::SubclassInputEditProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )     
	{         
	case WM_CHAR:              
		if ( (TCHAR)wParam == VK_RETURN ) // Found a RETURN keystroke!             
		{ 
			// get the command string
			long lSizeofString;

			// Get the size of the string
			lSizeofString = SendMessage( hWnd, WM_GETTEXTLENGTH, 0, 0 );

			// Get the string                 
			SendMessage( hWnd, WM_GETTEXT, lSizeofString + 1, (LPARAM) m_CommandBufferW ); 

			// send message to parent that command was entered
			SendMessage( m_hWnd, WM_USER, 0, lSizeofString );

			// clear the edit string
			SendMessage( hWnd, WM_SETTEXT, 0, (long) "" ); 
			return 1;
		}
	}

	return CallWindowProc( lpfnInputEdit, hWnd, message, wParam, lParam ); 
}

void ScriptConsole::Initialize(HINSTANCE hInstance)
{	
	m_hInstance = hInstance;
	m_iScrollPos = 0;

	// create application handler and link to our WindowProc
	WNDCLASS wc;

	// Set up and register window class
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC) MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(DWORD);
	wc.hInstance = m_hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"ConsoleWindow";

	RegisterClass( &wc );

	m_hWnd = CreateWindow( L"ConsoleWindow",	// class
		L"LUA WinConsole",		// caption
		WS_OVERLAPPEDWINDOW,	// style 
		700,					// left
		400,					// top
		480,					// width
		240,					// height
		NULL,					// parent window
		NULL,					// menu 
		m_hInstance,			// instance
		NULL );					// parms

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	SetFocus( m_hWnd );

	m_hEditControl = CreateWindow( L"EDIT",	// class
		L"",					// caption
		ES_LEFT | WS_CHILD, // style 
		0,					// left
		0,				// top
		0,				// width
		0,					// height
		m_hWnd,				// parent window
		(HMENU)0xa7,		// menu 
		m_hInstance,		// instance
		NULL );				// parms

	ShowWindow( m_hEditControl, SW_SHOW );
	UpdateWindow( m_hEditControl );
	SetFocus( m_hEditControl );

	lpfnInputEdit = (WNDPROC)SetWindowLong( m_hEditControl, GWL_WNDPROC, (long) SubclassInputEditProc ); 
	gScriptConsole->ResizeControls();
}
