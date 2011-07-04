//------------------------------------------------------------------------|
#pragma once

//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "IEvent.h"
#include "IEventHandler.h"
#include "IEventManager.h"
//------------------------------------------------------------------------|
namespace MG3
{
	typedef std::vector<IEventHandler*>	EventHandlerList;
	typedef std::vector<EventType>			EventTypeList;

	class EventManager : IEventManager
	{
	public:
		EventManager(wchar_t const* const pName, bool bSetAsGlobal);
		~EventManager();


		virtual bool RegisterEvent(EventType const& Type, IEventHandler* pHandler);
		virtual bool UnregisterEvent(EventType const& Type, IEventHandler* pHandler);
		virtual bool UnregisterAllEvents(IEventHandler* pHandler);
		virtual bool Fire(IEventData const& Event) const;
		//virtual bool QueueEvent(IEventDataPtr const& Event);
		//virtual bool AbortEvent(EventType const& Type, bool bAll = false);
		//virtual bool Tick(unsigned long maxMillis = kINFINITE);
		virtual bool ValidateType(EventType const& Type) const;
		
		void AddEvent(EventType const& Type);

	protected:

		typedef std::set<EventType>							EventTypeSet;
		typedef std::pair<EventTypeSet::iterator, bool>		EventTypeSetIRes;
		typedef std::list<IEventHandler*>					EventHandlerTable;
		typedef std::map<unsigned int, EventHandlerTable>	EventHandlerMap;
		typedef std::pair<unsigned int, EventHandlerTable>	EventHandlerMapEnt;
		typedef std::pair<EventHandlerMap::iterator, bool>	EventHandlerMapIRes;
		//typedef std::list<IEventDataPtr>					EventQueue;

		enum eConstans
		{
			kNumQueues = 2
		};

		EventTypeSet	m_TypeList;
		EventHandlerMap	m_Registry;
		//EventQueue		m_EventQueue[kNumQueues];
		int				m_iActiveQueue;
	};	
}