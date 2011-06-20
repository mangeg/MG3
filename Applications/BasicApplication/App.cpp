#include "App.h"

BasicApplication App;

BasicApplication::BasicApplication()
{
}

bool BasicApplication::Initialize()
{
	m_pWindow = new W32Window();
	m_pWindow->SetTitle(std::wstring(L"MG3 Basic Application"));
	m_pWindow->Initialize();

	return true;
}

void BasicApplication::Update()
{

}

void BasicApplication::Exit()
{
}