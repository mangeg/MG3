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
					TArray<int> a;
					a.Add(2);
					a.Add(25);
					a.Add(35325);
					a.Add(2);
					a.Add(25);
					a.Add(35325);

					a.Remove(3535);

					for(int i = 0; i < a.Size(); i++)
					{
						std::stringstream ss;
						ss << a[i];
						ScriptConsole::Write(ss.str().c_str());
					}
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