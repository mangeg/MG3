//------------------------------------------------------------------------|
#include "App.h"
#include "ScriptConsole.h"
#include "EvtKeyboardChar.h"
//------------------------------------------------------------------------|
BasicApplication App;
//------------------------------------------------------------------------|
BasicApplication::BasicApplication()
{
}

bool BasicApplication::SetupComponents()
{
	return true;
}

bool BasicApplication::Initialize()
{
	m_pWindow = new W32Window();
	m_pWindow->SetTitle(std::wstring(L"MG3 Basic Application"));
	m_pWindow->Initialize();

	ScriptConsole::Init(m_hInstance);

	EventManager::Get()->RegisterEvent(KEYBOARD_CHAR, this);

	return true;
}

void BasicApplication::Update()
{
}

void BasicApplication::Exit()
{
}

void BasicApplication::UnloadComponents()
{
}

bool BasicApplication::HandleEvent(IEvent* pEvent)
{
	eEVENT e = pEvent->GetEventType();

	switch (e)
	{
	case KEYBOARD_CHAR:
		{
			EvtKeyboardChar* pChar = (EvtKeyboardChar*)pEvent;
			UINT key = pChar->GetCharacterCode();

			switch(key)
			{
			case 's':
				{
					ScriptConsole::Toggle();
					break;
				}
			}

			return true;
		}
	}

	return false;
}

std::wstring BasicApplication::GetName()
{
	return std::wstring(L"");
}