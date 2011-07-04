//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "App.h"
#include "ScriptConsole.h"
#include "EvtKeyboardChar.h"

#include "TArray.h"
#include "MX11SwapChainConfig.h"
#include "MX11PipelineManager.h"
#include "MX11Texture2DConfig.h"

#include "EventSnooper.h"

#include "IEventManager.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
BasicApplication App;
//------------------------------------------------------------------------|
BasicApplication::BasicApplication()
{	
	std::wstring t = FileSystem::GetWorkingDirectory();
	FileSystem::GetFileName(t);
	t = FileSystem::GetDirectory(t);
}
//------------------------------------------------------------------------|
bool BasicApplication::SetupComponents()
{
	return true;
}
//------------------------------------------------------------------------|
bool BasicApplication::Initialize()
{	
	Log::Get().Write(L"Application started");

	m_pWindow = new W32Window();
	m_pWindow->SetTitle(std::wstring(L"MG3 Basic Application"));
	m_pWindow->Initialize();

	// Event manager
	m_pEventManager = MG_NEW EventManager(L"MainEvents", true);			
	//m_pEventManager->RegisterEvent(skAllEvents, EventHandlerPtr(MG_NEW EventSnooper()));

	m_pEventManager->AddEvent(EvtKeyboardChar::m_sEventType);

	m_pEventManager->RegisterEvent(EvtKeyboardChar::m_sEventType, this);

	// Console
	ScriptConsole::Init(m_hInstance);

	// Renderer
	m_pRenderer = new MX11Renderer();
	if(!m_pRenderer->Initialize())
		return false;

	MX11SwapChainConfig config;
	config.SetWidth(m_pWindow->GetWidth());
	config.SetHeight(m_pWindow->GetHeight());
	config.SetOutputWindow(m_pWindow->GetHandle());

	m_iSwapChain = m_pRenderer->CreateSwapchain(&config);
	m_pWindow->SetSwapChain(m_iSwapChain);

	ResourcePtr RenderTarget = m_pRenderer->GetSwapChainResource(m_iSwapChain);

	MX11Texture2DConfig DeptConfig;
	DeptConfig.SetDepthBuffer(m_pWindow->GetWidth(), m_pWindow->GetHeight());
	ResourcePtr DeptTarget = m_pRenderer->CreateTexture2D(&DeptConfig, NULL);

	m_pRenderer->m_pPipeline->ClearRenderTargets();
	m_pRenderer->m_pPipeline->BindRenderTarget(0, RenderTarget);
	m_pRenderer->m_pPipeline->BindDeptTarget(DeptTarget);
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
//------------------------------------------------------------------------|
void BasicApplication::Update()
{
	m_pTimer->Update();

	float fBlue = sinf( m_pTimer->GameTime() ) * 0.25f + 0.5f;
	//fBlue = 0.2;
	m_pRenderer->m_pPipeline->ClearBuffers(XMFLOAT4(0.0f, 0.2f, fBlue, 1.0f));
	m_pRenderer->Present(m_pWindow->GetSwapChain());
}
//------------------------------------------------------------------------|
void BasicApplication::Exit()
{
	Log::Get() << L"Max FPS: " << m_pTimer->MaxFrameRate() << std::endl 
		<< L"Game time: " << m_pTimer->GameTime() << "s" << Flush;

	m_pEventManager->UnregisterAllEvents(this);	
	SAFE_DELETE(m_pEventManager);
}
//------------------------------------------------------------------------|
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
//------------------------------------------------------------------------|
bool BasicApplication::HandleEvent(IEventData const& pEvent)
{
	if(EvtKeyboardChar::m_sEventType == pEvent.GetEventType())
	{
		const EvtKeyboardChar & castEvent = static_cast< const EvtKeyboardChar & >( pEvent );
		const unsigned int key = castEvent.GetCharacterCode();
		
		switch(key)
		{
		case 't':
			m_pTimer->Stop();
			break;
		case 'y':
			m_pTimer->Start();
			break;
		case 'u':
			m_pTimer->Toggle();
			break;
		case VK_ESCAPE:
			this->DoExit();
			break;
		}
		
	}

	return false;
}
//------------------------------------------------------------------------|
std::wstring BasicApplication::GetName()
{
	return std::wstring(L"BasicApplication");
}