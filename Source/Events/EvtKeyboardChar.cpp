//------------------------------------------------------------------------|
#include "EvtKeyboardChar.h"
//------------------------------------------------------------------------|
using namespace MG3;
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
std::wstring EvtKeyboardChar::GetName()
{
	return std::wstring(L"EvtKeyboard::Char");
}
//------------------------------------------------------------------------|
eEVENT EvtKeyboardChar::GetEventType()
{
	return KEYBOARD_CHAR;
}