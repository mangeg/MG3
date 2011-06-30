//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "EventManager.h"

//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
EventManager* EventManager::m_spInstance = NULL;

//------------------------------------------------------------------------|
EventManager::EventManager()
{
	if(!m_spInstance)
		m_spInstance = this;
}

//------------------------------------------------------------------------|
EventManager::~EventManager()
{
}

//------------------------------------------------------------------------|
bool EventManager::RegisterEvent(eEVENT EventType, IEventHandler* pHandler)
{
	if(EventType > NUM_EVENTS)
		return false;

	m_EventHandlers[EventType].push_back(pHandler);

	return true;
}

//------------------------------------------------------------------------|
bool EventManager::UnregisterEvent(eEVENT EventType, IEventHandler* pHandler)
{
	if(EventType > NUM_EVENTS)
		return false;

	m_EventHandlers[EventType].remove(pHandler);

	return true;
}

//------------------------------------------------------------------------|
bool EventManager::Fire(IEvent* pEvent)
{
	if(!pEvent)
		return false;

	eEVENT e = pEvent->GetEventType();
	bool handled = false;

	std::list<IEventHandler*>::iterator it = m_EventHandlers[e].begin();
	for( ; it != m_EventHandlers[e].end(); it++)
	{
		bool h = (*it)->HandleEvent(pEvent);
		if(h)
			handled = true;
	}

	delete pEvent;
	return true;
}

//------------------------------------------------------------------------|
EventManager* EventManager::Get()
{
	return m_spInstance;
}