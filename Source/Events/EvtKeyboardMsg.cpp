//------------------------------------------------------------------------|
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
unsigned int EvtKeyboardMsg::GetCharacterCode()
{
	return  m_iWParam;
}
//------------------------------------------------------------------------|
unsigned int EvtKeyboardMsg::GetRepeatCount()
{
	return 0xffff & m_iLParam;
}
//------------------------------------------------------------------------|
unsigned int EvtKeyboardMsg::GetScanCode()
{
	return ( 0xf0000 & m_iLParam ) >> 16;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetExtendedKey()
{
	return ( 0x01000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetContextCode()
{
	return ( 0x20000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetPreviousKeyState()
{
	return ( 0x40000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|
bool EvtKeyboardMsg::GetTransitionState()
{
	return ( 0x80000000 & m_iLParam ) > 0;
}
//------------------------------------------------------------------------|