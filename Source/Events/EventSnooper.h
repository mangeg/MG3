//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IEventHandler.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class EventSnooper : public IEventHandler
	{
	public:
		EventSnooper();
		virtual ~EventSnooper();

		std::wstring GetName() { return std::wstring(L"Snooper"); }
		bool HandleEvent(IEventData const& pEvent);

	protected:
		
	};
}