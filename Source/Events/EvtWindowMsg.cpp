//------------------------------------------------------------------------|
#include "EvtWindowsMsg.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
EvtWindowsMsg::EvtWindowsMsg(HWND hWnd, UINT wParam, UINT lParam)
{
	m_hWnd = hWnd;
	m_iWParam = wParam;
	m_iLParam = lParam;
}
//------------------------------------------------------------------------|
EvtWindowsMsg::~EvtWindowsMsg()
{
}
//------------------------------------------------------------------------|
HWND EvtWindowsMsg::GetWindowHandle()
{
	return m_hWnd;
}
//------------------------------------------------------------------------|
UINT EvtWindowsMsg::GetWParam()
{
	return m_iWParam;
}
//------------------------------------------------------------------------|
UINT EvtWindowsMsg::GetLParam()
{
	return m_iLParam;
}