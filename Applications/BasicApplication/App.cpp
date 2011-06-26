//------------------------------------------------------------------------|
#include "App.h"
#include "ScriptConsole.h"
#include "EvtKeyboardChar.h"

#include "TArray.h"

#include <sstream>
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

	m_pRenderer = new MX11Renderer();
	if(!m_pRenderer->Initialize())
		return false;

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
	if(m_pRenderer)
	{
		m_pRenderer->Shutdown();
		delete m_pRenderer;
	}

	if(m_pWindow)
	{
		m_pWindow->Exit();
		delete m_pWindow;
	}
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
	return std::wstring(L"BasicApplication");
}