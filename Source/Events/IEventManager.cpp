//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "IEventManager.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
static IEventManager* g_pEventMgr = NULL;
//------------------------------------------------------------------------|
IEventManager::IEventManager(wchar_t const* const pName, bool bSetAsGlobal)
{
	if(bSetAsGlobal)
		g_pEventMgr = this;
}
//------------------------------------------------------------------------|
IEventManager::~IEventManager()
{
	if(g_pEventMgr == this)
		g_pEventMgr = NULL;
}
//------------------------------------------------------------------------|
IEventManager* IEventManager::Get()
{
	return g_pEventMgr;
}
//------------------------------------------------------------------------|
namespace MG3
{
	
	bool safeRegisterEvent( EventType const& Type, IEventHandler* Handler )
	{
		assert(IEventManager::Get() && L"No event manager!");
		return IEventManager::Get()->RegisterEvent( Type, Handler );
	}
	bool safeFireEvent(IEventData const& Event)
	{
		assert(IEventManager::Get() && L"No event manager!");
		return IEventManager::Get()->Fire(Event);
	}
}