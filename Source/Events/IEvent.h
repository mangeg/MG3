//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IEventData.h"
#include "boost/shared_ptr.hpp"
//------------------------------------------------------------------------|
namespace MG3
{
	typedef boost::shared_ptr<IEventData> IEventDataPtr;

	class IEvent : public IEventData
	{
	public:
		explicit IEvent( const float fTimeStamp = 0.0f)
			: m_fTimeStamp(fTimeStamp)
		{}
		virtual ~IEvent() {}

		virtual const EventType& GetEventType() const = 0;
		const float GetTimeStamp() const { return m_fTimeStamp; }
		virtual void Serialize(std::ostream &out) const { };

	protected:
		const float m_fTimeStamp;
	};
}