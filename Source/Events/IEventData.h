//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "HashedString.h"
//------------------------------------------------------------------------|
namespace MG3
{
	typedef HashedString EventType;

	class IEventData
	{
	public:
		virtual const EventType& GetEventType(void) const = 0;
		virtual float GetTimeStamp() const = 0;
		virtual void Serialize(std::ostream &out) const = 0;
	};
}