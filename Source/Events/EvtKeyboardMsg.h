//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "EvtWindowsMsg.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class EvtKeyboardMsg : public EvtWindowsMsg
	{
	public:
		EvtKeyboardMsg(HWND hWnd, UINT wParam, UINT lParam);
		virtual ~EvtKeyboardMsg();

		unsigned int GetCharacterCode();
		unsigned int GetRepeatCount();
		unsigned int GetScanCode();
		bool GetExtendedKey();
		bool GetContextCode();
		bool GetPreviousKeyState();
		bool GetTransitionState();
	};
}