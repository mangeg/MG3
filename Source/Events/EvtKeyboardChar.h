//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MG3.h"
#include "EvtKeyboardMsg.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class EvtKeyboardChar : public EvtKeyboardMsg
	{
	public:
		EvtKeyboardChar(HWND hWnd, UINT wParam, UINT lParam);
		~EvtKeyboardChar();

		virtual std::wstring GetName();
		virtual eEVENT GetEventType();
	};
}