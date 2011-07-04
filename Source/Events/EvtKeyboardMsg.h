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

		virtual const EventType& GetEventType() const = 0;
		virtual void Serialize(std::ostream &out) const { };

		unsigned int GetCharacterCode() const;
		unsigned int GetRepeatCount() const;
		unsigned int GetScanCode() const;
		bool GetExtendedKey() const;
		bool GetContextCode() const;
		bool GetPreviousKeyState() const;
		bool GetTransitionState() const;
	};
}