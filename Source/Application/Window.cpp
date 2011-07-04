#include "StdAfx.h"
#include "Window.h"

using namespace MG3;
//------------------------------------------------------------------------|
Window::Window()
{
	m_hWnd = NULL;
	m_dStyle = (WS_OVERLAPPEDWINDOW | WS_VISIBLE) & ~WS_THICKFRAME;
	m_sTitle = L"";
	m_iWidth = 800;
	m_iHeight = 600;
	m_iLeft = 300;
	m_iTop = 200;
}
//------------------------------------------------------------------------|
Window::~Window()
{
}
//------------------------------------------------------------------------|
HWND Window::GetHandle()
{
	return m_hWnd;
}
//------------------------------------------------------------------------|
void Window::SetWidth(int width)
{
	m_iWidth = width;
	_UpdateWindowState();
}
//------------------------------------------------------------------------|
void Window::SetHeight(int height)
{
	m_iHeight = height;
	_UpdateWindowState();
}
//------------------------------------------------------------------------|
void Window::SetTitle(std::wstring& title)
{
	m_sTitle = title;

	if(m_hWnd != NULL)
		SetWindowText(m_hWnd, m_sTitle.c_str());
}
//------------------------------------------------------------------------|
std::wstring Window::GetTitle()
{
	return m_sTitle;
}
//------------------------------------------------------------------------|
int Window::GetHeight()
{
	return m_iHeight;
}
//------------------------------------------------------------------------|
int Window::GetWidth()
{
	return m_iWidth;
}
//------------------------------------------------------------------------|
void Window::SetSwapChain(int iSwapChain)
{
	m_iSwapChain = iSwapChain;
}
//------------------------------------------------------------------------|
int Window::GetSwapChain()
{
	return m_iSwapChain;
}
//------------------------------------------------------------------------|
void Window::_UpdateWindowState()
{
	if(m_hWnd != 0)
	{
		RECT ClientRect;
		ClientRect.left = 0;
		ClientRect.top = 0;
		ClientRect.right = m_iWidth;
		ClientRect.bottom = m_iHeight;

		RECT WindowRect = ClientRect;
		AdjustWindowRect(&WindowRect, m_dStyle, FALSE);

		int deltaX = (WindowRect.right - ClientRect.right) / 2;
		int deltaY = (WindowRect.bottom - ClientRect.bottom) / 2;

		//MoveWindow( m_hWnd, m_iLeft - deltaX, m_iTop - deltaY, m_iWidth + deltaX * 2, m_iHeight + deltaY * 2, true );
	}
}