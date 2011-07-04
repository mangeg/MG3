//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IEvent.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class IEventHandler
	{
	public:
		IEventHandler() {};
		virtual ~IEventHandler() {};

		virtual std::wstring GetName() = 0;
		virtual bool HandleEvent(IEventData const& event) = 0
		{
			return true;
		}
	};
}