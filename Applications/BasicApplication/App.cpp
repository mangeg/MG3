//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "App.h"
#include "ScriptConsole.h"
#include "EvtKeyboardChar.h"

#include "TArray.h"
#include "MX11SwapChainConfig.h"
#include "MX11PipelineManager.h"
#include "MX11ParameterManager.h"
#include "MX11VectorParameter.h"
#include "MX11BufferConfig.h"
#include "MX11Texture2DConfig.h"
#include "MX11RasterizerStateConfig.h"

#include "MX11Shader.h"
#include "MX11VertexShader.h"

#include "MX11RenderEffect.h"

#include "EventSnooper.h"

#include "IEventManager.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
BasicApplication App;
struct VERTEX{FLOAT X, Y, Z; D3DXCOLOR Color;};
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
	//m_pRenderer->m_pPipeline->BindDeptTarget(DeptTarget);
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

	std::wstring wd = FileSystem::GetWorkingDirectory();
	m_pEffect = new MX11RenderEffect();
	m_pEffect->m_iVertexShader = m_pRenderer->LoadShader(SHADER_VERTEX, (wd + L"Shaders\\basic.hlsl"), L"VShader", L"vs_5_0");
	m_pEffect->m_iPixelShader = m_pRenderer->LoadShader(SHADER_PIXEL, (wd + L"Shaders\\basic.hlsl"), L"PShader", L"ps_5_0");

	HRESULT hr = S_OK;

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	TArray<D3D11_INPUT_ELEMENT_DESC> elemets;
	elemets.Add(ied[0]);
	elemets.Add(ied[1]);

	int InputLayoutID = m_pRenderer->CreateInputLayout(elemets, m_pEffect->m_iVertexShader);
	m_pRenderer->m_pPipeline->SetInputLayout(InputLayoutID);

	VERTEX OurVertices[] =
	{
		{0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
		{-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
		{0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
		{-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)},
		{-0.45f, 0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},		
	};

	// create the vertex buffer
	D3D11_SUBRESOURCE_DATA BufferData;
	BufferData.pSysMem = reinterpret_cast<void*>(OurVertices);
	BufferData.SysMemPitch = 0;
	BufferData.SysMemSlicePitch = 0;

	MX11BufferConfig vbuffer;
	vbuffer.SetDefaultVertexBuffer(sizeof(VERTEX) * 6, false);
	VertexBuffer = m_pRenderer->CreateVertexBuffer(&vbuffer, &BufferData);

	MX11RasterizerStateConfig RasterizerStateConfig;
	RasterizerStateConfig.FillMode = D3D11_FILL_WIREFRAME;
	int RasterizerStateID = m_pRenderer->CreateRasterizerState(&RasterizerStateConfig);

	//m_pEffect->m_iRasterizerState = RasterizerStateID;	

	m_pVectorParam = m_pRenderer->m_pParamManager->GetVectorParamRef(HashedString(std::wstring(L"TexAndViewportSize").c_str()));

	return true;
}
//------------------------------------------------------------------------|
void BasicApplication::Update()
{
	m_pTimer->Update();

	float fBlue = sinf( static_cast<float>(m_pTimer->GameTime()) ) * 0.25f + 0.5f;

	m_pVectorParam->SetVector(XMFLOAT4(fBlue - 0.5, 0, 0, 1));

	m_pRenderer->m_pPipeline->ClearBuffers(XMFLOAT4(0.0f, 0.2f, 0.25, 1.0f));	

	m_pEffect->ApplyEffect(m_pRenderer->m_pPipeline, m_pRenderer->m_pParamManager);

	// select which vertex buffer to display
	m_pRenderer->m_pPipeline->BindVertexBuffer(VertexBuffer, sizeof(VERTEX), 0);

	// select which primitive type we are using
	m_pRenderer->m_pPipeline->GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pRenderer->m_pPipeline->ApplyPipelineResource();

	// draw the vertex buffer to the back buffer
	m_pRenderer->m_pPipeline->GetContext()->Draw(6, 0);

	m_pRenderer->Present(m_pWindow->GetSwapChain());
}
//------------------------------------------------------------------------|
void BasicApplication::Exit()
{
	Log::Get() << L"Max FPS: " << m_pTimer->MaxFrameRate() << std::endl 
		<< L"Game time: " << m_pTimer->GameTime() << "s" << Flush;

	m_pEventManager->UnregisterAllEvents(this);	

	SAFE_DELETE(m_pEffect);
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