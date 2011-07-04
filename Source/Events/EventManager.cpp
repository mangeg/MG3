//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "EventManager.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
EventManager::EventManager(wchar_t const* const pName, bool bSetAsGlobal)
	: IEventManager(pName, bSetAsGlobal),
	m_iActiveQueue(0)
{
}
//------------------------------------------------------------------------|
EventManager::~EventManager()
{
	m_iActiveQueue = 0;
}
//------------------------------------------------------------------------|
bool EventManager::RegisterEvent(EventType const& Type, IEventHandler* pHandler)
{
	if(!ValidateType(Type))
		return false;

	EventHandlerMap::iterator elmIt = m_Registry.find(Type.GetIdent());

	// If this event is not registered at all yet, initialize a list of handlers for this event.
	if(elmIt == m_Registry.end())
	{
		EventHandlerMapIRes elmIRes = m_Registry.insert(
			EventHandlerMapEnt(Type.GetIdent(), EventHandlerTable()));

		if(!elmIRes.second)
			return false;
		if(elmIRes.first == m_Registry.end())
			return false;

		elmIt = elmIRes.first;
	}

	EventHandlerTable& evhTable = (*elmIt).second;

	// Check if event is already registered
	for(EventHandlerTable::iterator it = evhTable.begin(), itEnd = evhTable.end(); it != itEnd; it++)
	{
		bool bHandlerMatch = (*it == pHandler);
		if(bHandlerMatch)
			return false;
	}

	evhTable.push_back(pHandler);

	return true;
}
//------------------------------------------------------------------------|
bool EventManager::UnregisterEvent(EventType const& Type, IEventHandler* pHandler)
{
	if(!ValidateType(Type))
		return false;

	bool rc = false;
	
	// Find the currently registered handlers for the event.
	EventHandlerMap::iterator elmIt = m_Registry.find(Type.GetIdent());

	if(elmIt != m_Registry.end())
	{
		EventHandlerTable& table = elmIt->second;
		for(EventHandlerTable::iterator it2 = table.begin(), it2End = table.end(); it2 != it2End; it2++)
		{
			if(*it2 == pHandler)
			{
				table.erase(it2);
				rc = true;
				break;
			}
		}
	}

	return rc;
}
//------------------------------------------------------------------------|
bool EventManager::UnregisterAllEvents(IEventHandler* pHandler)
{
	for(EventHandlerMap::iterator it = m_Registry.begin(), itEnd = m_Registry.end(); it != itEnd; it++)
	{
		EventHandlerTable& table = it->second;

		for(EventHandlerTable::iterator it2 = table.begin(), it2End = table.end(); it2 != it2End; it2++)
		{
			if(*it2 == pHandler)
			{
				table.erase(it2);
				break;
			}
		}
	}

	return true;
}
//------------------------------------------------------------------------|
bool EventManager::Fire(IEventData const& Event) const
{
	if(!ValidateType(Event.GetEventType()))
		return false;

	// Find all handlers that listen to all events
	EventHandlerMap::const_iterator itWC = m_Registry.find(skAllEvents.GetIdent());

	if(itWC != m_Registry.end())
	{
		EventHandlerTable const& table = itWC->second;
		for(EventHandlerTable::const_iterator it2 = table.begin(), it2End = table.end(); it2 != it2End; it2++)
		{
			(*it2)->HandleEvent(Event);
		}
	}

	EventHandlerMap::const_iterator it = m_Registry.find(Event.GetEventType().GetIdent());
	if(it == m_Registry.end())
		return false;
	EventHandlerTable const& table = it->second;
	bool processed = false;

	for(EventHandlerTable::const_iterator it2 = table.begin(), it2End = table.end(); it2 != it2End; it2++)
	{
		if((*it2)->HandleEvent(Event))
		{
			processed = true;
		}
	}

	return processed;
}
//------------------------------------------------------------------------|
bool EventManager::ValidateType(EventType const& Type) const
{
	if(0 == Type.GetStr().length())
		return false;
	if(Type == skAllEvents)
		return true;
	if(Type.GetIdent() == 0 && wcscmp(Type.GetStr().c_str(), skpWildCardEventType) == 0)
		return false;

	EventTypeSet::const_iterator evIt = m_TypeList.find(Type);

	if(evIt == m_TypeList.end())
		return false;

	return true;
}
//------------------------------------------------------------------------|
void EventManager::AddEvent(const EventType& Type)
{
	const EventTypeSet::const_iterator it = m_TypeList.find(Type);
	if(it != m_TypeList.end())
	{
		assert( 0 && "Attempted to register an event type that has already been registered!" );
	}
	else
	{
		m_TypeList.insert(Type);
	}
}