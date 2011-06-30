//------------------------------------------------------------------------|
#pragma once

//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "IEvent.h"
#include "IEventHandler.h"

//------------------------------------------------------------------------|
namespace MG3
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		bool RegisterEvent(eEVENT EventType, IEventHandler* pHandler);
		bool UnregisterEvent(eEVENT EventType, IEventHandler* pHandler);
		bool Fire(IEvent* pEvent);

		static EventManager* Get();
	protected:

		std::list<IEventHandler*> m_EventHandlers[NUM_EVENTS];

		static EventManager* m_spInstance;
	};
}