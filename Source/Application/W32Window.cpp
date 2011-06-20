#include "W32Window.h"

using namespace MG3;

const wchar_t* WindowClassName = L"MG3WindowClass";
extern LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

W32Window::W32Window()
{
	m_hWnd = 0;
}

W32Window::~W32Window()
{
	Exit();
}

void W32Window::Initialize()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WindowProc;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW); 
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName	= WindowClassName;
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	m_dStyle = (WS_OVERLAPPEDWINDOW | WS_VISIBLE) & ~WS_THICKFRAME;

	RECT wr = {0, 0, m_iWidth, m_iHeight};
	AdjustWindowRect(&wr, m_dStyle, FALSE);

	m_hWnd = CreateWindowEx(
		NULL,
		WindowClassName,
		m_sTitle.c_str(),
		m_dStyle,
		m_iLeft, m_iTop,
		m_iWidth, m_iHeight,
		NULL,
		NULL,
		NULL,
		NULL);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
}

void W32Window::Exit()
{
	if(m_hWnd)
		DestroyWindow(m_hWnd);

	m_hWnd = 0;
}

void W32Window::Paint()
{
}