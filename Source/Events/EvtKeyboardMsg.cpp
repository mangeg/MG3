//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "EvtKeyboardMsg.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
EvtKeyboardMsg::EvtKeyboardMsg(HWND hWnd, UINT wParam, UINT lParam)
	:EvtWindowsMsg(hWnd, wParam, lParam)
{
}
//------------------------------------------------------------------------|
EvtKeyboardMsg::~EvtKeyboardMsg()
{
}
//------------------------------------------------------------------------|
unsigned int EvtKeyboardMsg::GetCharacterCode() const
{
	return  m_iWParam;
}
//------------------------------------------------------------------------|
unsigned int EvtKeyboardMsg::GetRepeatCount() const
{
	return 0xffff & m_iLParam;
}
//------------------------------------------------------------------------|
unsigned int EvtKeyboardMsg::GetScanCode() const
{
	return ( 0xf0000 & m_iLParam ) >> 16;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetExtendedKey() const
{
	return ( 0x01000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetContextCode() const
{
	return ( 0x20000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetPreviousKeyState() const
{
	return ( 0x40000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetTransitionState() const
{
	return ( 0x80000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|