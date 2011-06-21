#include "App.h"

BasicApplication App;

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

	EventManager::Get()->RegisterEvent(KEYBOARD_KEYDOWN, this);

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
	case KEYBOARD_KEYDOWN:
		return true;
	}

	return false;
}

std::wstring BasicApplication::GetName()
{
	return std::wstring(L"");
}