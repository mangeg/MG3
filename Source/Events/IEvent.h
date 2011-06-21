//------------------------------------------------------------------------|
#pragma once

//------------------------------------------------------------------------|
#include <string>

//------------------------------------------------------------------------|
namespace MG3
{
	enum eEVENT
	{
		KEYBOARD_KEYDOWN,
		KEYBOARD_KEYUP,
		KEYBOARD_CHAR,
		NUM_EVENTS,
	};

	class IEvent
	{
	public:
		IEvent();
		virtual ~IEvent();

		virtual std::wstring GetName() = 0;
		virtual eEVENT GetEventType() = 0;
	};
}