//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "EvtKeyboardMsg.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class EvtKeyboardChar : public EvtKeyboardMsg
	{
	public:
		EvtKeyboardChar(HWND hWnd, UINT wParam, UINT lParam);
		~EvtKeyboardChar();

		virtual const EventType& GetEventType() const;

		static const EventType m_sEventType;
	};	
}