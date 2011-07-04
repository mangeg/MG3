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
		virtual const EventType& GetEventType() const = 0;
		virtual const float GetTimeStamp() const = 0;
		virtual void Serialize(std::ostream &out) const = 0;
	};
}