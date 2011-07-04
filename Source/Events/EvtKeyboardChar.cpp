//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "EvtKeyboardChar.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
const EventType EvtKeyboardChar::m_sEventType(L"Keyboard_Char");
//------------------------------------------------------------------------|
EvtKeyboardChar::EvtKeyboardChar(HWND hWnd, UINT wParam, UINT lParam)
	: EvtKeyboardMsg(hWnd, wParam, lParam)
{
}
//------------------------------------------------------------------------|
EvtKeyboardChar::~EvtKeyboardChar()
{
}
//------------------------------------------------------------------------|
EventType const& EvtKeyboardChar::GetEventType() const
{
	return EvtKeyboardChar::m_sEventType;
}