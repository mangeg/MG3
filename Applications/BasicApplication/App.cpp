//------------------------------------------------------------------------|
#include "App.h"
#include "ScriptConsole.h"
#include "EvtKeyboardChar.h"

#include "TArray.h"
#include "MX11SwapChainConfig.h"
#include "MX11PipelineManager.h"

#include "HashedString.h"

#include <sstream>
//------------------------------------------------------------------------|
BasicApplication App;
//------------------------------------------------------------------------|
BasicApplication::BasicApplication()
{
	HashedString s(L"afsasf");
	char* saf = new char[35];
}
//------------------------------------------------------------------------|
bool BasicApplication::SetupComponents()
{
	return true;
}
//------------------------------------------------------------------------|
bool BasicApplication::Initialize()
{
	m_pWindow = new W32Window();
	m_pWindow->SetTitle(std::wstring(L"MG3 Basic Application"));
	m_pWindow->Initialize();

	EventManager::Get()->RegisterEvent(KEYBOARD_CHAR, this);

	ScriptConsole::Init(m_hInstance);

	m_pRenderer = new MX11Renderer();
	if(!m_pRenderer->Initialize())
		return false;

	MX11SwapChainConfig config;
	config.SetWidth(m_pWindow->GetWidth());
	config.SetHeight(m_pWindow->GetHeight());
	config.SetOutputWindow(m_pWindow->GetHandle());

	m_iSwapChain = m_pRenderer->CreateSwapchain(&config);
	m_pWindow->SetSwapChain(m_iSwapChain);

	m_RenderTarget = m_pRenderer->GetSwapChainResource(m_iSwapChain);

	m_pRenderer->m_pPipeline->ClearRenderTargets();
	m_pRenderer->m_pPipeline->BindRenderTarget(0, m_RenderTarget);
	m_pRenderer->m_pPipeline->ApplyRenderTargets();

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast< float >( m_pWindow->GetWidth() );
	viewport.Height = static_cast< float >( m_pWindow->GetHeight() );
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	int ViewpPort = m_pRenderer->CreateViewPort(viewport);
	m_pRenderer->m_pPipeline->SetViewPort(ViewpPort);

	return true;
}

void BasicApplication::Update()
{
	m_pRenderer->m_pPipeline->ClearBuffers(XMFLOAT4(0.0f, 0.2f, 0.4f, 1.0f));
	m_pRenderer->Present(m_pWindow->GetSwapChain());
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