//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IEventData.h"
#include "boost/shared_ptr.hpp"
//------------------------------------------------------------------------|
namespace MG3
{
	typedef boost::shared_ptr<IEventData> IEventDataPtr;

	class BaseEventData : public IEventData
	{
	public:
		explicit BaseEventData( const float fTimeStamp = 0.0f)
			: m_fTimeStamp(fTimeStamp)
		{}
		virtual ~BaseEventData() {}

		virtual const EventType& GetEventType(void)  = 0;
		float GetTimeStamp(void) const {return m_fTimeStamp;}
		virtual void Serialize(std::ostream &out) const {}

	protected:
		const float m_fTimeStamp;
	};
}