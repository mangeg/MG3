//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "EventSnooper.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
EventSnooper::EventSnooper()
{
}
//------------------------------------------------------------------------|
EventSnooper::~EventSnooper()
{
}
//------------------------------------------------------------------------|
bool EventSnooper::HandleEvent(IEventData const& Event)
{
	std::wstringstream s;	
#ifdef _DEBUG	
#pragma warning( push )
#pragma warning( disable : 4313 ) 
	wchar_t m_msgBuf[4090];
	 memset( m_msgBuf, 0, sizeof(m_msgBuf));
	_snwprintf_s( m_msgBuf, sizeof(m_msgBuf)-1,
		L"Event Snoop : event %08lx time %g : type %08lx [%s]",
		&Event,
		Event.GetTimeStamp(),
		Event.GetEventType().GetIdent(),
		Event.GetEventType().GetStr().c_str()
		);

	OutputDebugString(m_msgBuf);
	OutputDebugString(L"\n");
#pragma warning( pop )
#endif
	
	return false;
}