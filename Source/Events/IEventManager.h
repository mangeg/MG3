//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IEventHandler.h"
//------------------------------------------------------------------------|
namespace MG3
{
	static wchar_t const* skpWildCardEventType = L"*";
	static const EventType skAllEvents(skpWildCardEventType);

	class IEventManager
	{
	public:
		enum eConstants
		{
			kINFINITE = 0xffffffff
		};

		explicit IEventManager(wchar_t const* const pName, bool bSetAsGlobal);
		virtual ~IEventManager();

		virtual bool RegisterEvent(EventType const& Type, IEventHandler* pHandler) = 0;
		virtual bool UnregisterEvent(EventType const& Type, IEventHandler* pHandler) = 0;
		virtual bool Fire(IEventData const& Event) const = 0;
		//virtual bool QueueEvent(IEventDataPtr const& Event) = 0;
		//virtual bool AbortEvent(EventType const& Type, bool bAll = false) = 0;
		//virtual bool Tick(unsigned long maxMillis = kINFINITE) = 0;
		virtual bool ValidateType(EventType const& Type) const = 0;

		static IEventManager* Get();

	private:		
		friend bool safeRegisterEvent(EventType const& Type, IEventHandler* Handler);
		friend bool safeFireEvent(IEventData const& Event);
	};

	bool safeRegisterEvent( EventType const& Type, IEventHandler* Handler );
	bool safeFireEvent(IEventData const& Event);
}
