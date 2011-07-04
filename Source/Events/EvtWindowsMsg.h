//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "IEvent.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class EvtWindowsMsg : public IEvent
	{
	public:
		EvtWindowsMsg(HWND hWnd, UINT wParam, UINT lParam);
		virtual ~EvtWindowsMsg();

		virtual const EventType& GetEventType() const = 0;
		virtual void Serialize(std::ostream &out) const { };

		HWND GetWindowHandle();
		UINT GetWParam();
		UINT GetLParam();

	protected:
		HWND	m_hWnd;
		UINT	m_iWParam;
		UINT	m_iLParam;
	};
}