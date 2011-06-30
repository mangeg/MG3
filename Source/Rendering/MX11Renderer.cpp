//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Renderer.h"

#include "MX11ViewPort.h"

#include "MX11RenderTargetView.h"

#include "MX11SwapChainConfig.h"
#include "MX11Texture2DConfig.h"

#include "MX11ResourceProxy.h"
#include "MX11SwapChain.h"
#include "MX11Texture2D.h"

#include "DXGIAdapter.h"
#include "MX11PipelineManager.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------| 
MX11Renderer* MX11Renderer::m_spRenderer = NULL;
//------------------------------------------------------------------------|
MX11Renderer::MX11Renderer()
{
	if(m_spRenderer == 0)
		m_spRenderer = this;

	m_pDevice = NULL;
	m_pDebugger = NULL;
}
//------------------------------------------------------------------------|
MX11Renderer::~MX11Renderer()
{
}
//------------------------------------------------------------------------|
bool MX11Renderer::Initialize()
{
	HRESULT hr;

	// Create factory
	IDXGIFactory1* pFactory;	
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&pFactory));	
	if(FAILED(hr))
	{
		DXTRACE_ERR(L"Could not create DXGIFactory", hr);
		return false;
	}

	// Enumerate adapters
	IDXGIAdapter1* pAdapter;
	TArray<DXGIAdapter*> vAdapters;
	while(pFactory->EnumAdapters1(vAdapters.Size(), &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGIAdapter* a = new DXGIAdapter(pAdapter);
		vAdapters.Add( a );
	}

	// Device flags
	UINT CreateDeviceFlags = 0;
#ifdef _DEBUG
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		
	// Driver types and feature levels
	D3D_DRIVER_TYPE vDriverTypes [] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE };
	D3D_FEATURE_LEVEL vFeatureLevels [] = { D3D_FEATURE_LEVEL_11_0 };

	// Create device and context
	ID3D11DeviceContext* pContext = 0;
	for(int i = 0; i < ARRAYSIZE(vDriverTypes); i++)
	{
		hr = D3D11CreateDevice(
			0,
			vDriverTypes[i],
			0,
			CreateDeviceFlags,
			vFeatureLevels,
			ARRAYSIZE(vFeatureLevels),
			D3D11_SDK_VERSION,
			&m_pDevice,
			0,
			&pContext);

		if(SUCCEEDED(hr))
		{
			break;
		}
	}

	if(FAILED(hr))
	{
		DXTRACE_ERR(L"No device crated, last error: ", hr);
		return false;
	}

	m_pPipeline = new MX11PipelineManager();
	m_pPipeline->SetDeviceContext(pContext);

	// Release adapters and factory
	for(int i = 0; i < vAdapters.Size(); i++)
		delete vAdapters[i];
	SAFE_RELEASE(pFactory);

	// Get debug interface
	/*
	hr = m_pDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&m_pDebugger));
	if(FAILED(hr))
	{
		Shutdown();
		return false;
	}
	*/
	
	// Save the feature level the device got created with.
	m_FeatureLevel = m_pDevice->GetFeatureLevel();

	return true;
}
//------------------------------------------------------------------------|
void MX11Renderer::Shutdown()
{
	SAFE_DELETE(m_pPipeline);	

	for(int i = 0; i < m_vRenderTargetViews.Size(); i++)
		delete m_vRenderTargetViews[i];
	for(int i = 0; i < m_vResources.Size(); i++)
		delete m_vResources[i];
	for(int i = 0; i < m_vSwapChains.Size(); i++)
		delete m_vSwapChains[i];

	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDebugger);
}
//------------------------------------------------------------------------|
MX11Renderer* MX11Renderer::Get()
{
	return m_spRenderer;
}
//------------------------------------------------------------------------|
void MX11Renderer::Present(int iSwapChain)
{
	if(iSwapChain >= 0 && iSwapChain < m_vSwapChains.Size())
	{
		MX11SwapChain* pSwapChain = m_vSwapChains[iSwapChain];
		pSwapChain->m_pSwapChain->Present(0, 0);
	}
}
//------------------------------------------------------------------------|
int MX11Renderer::CreateSwapchain(MX11SwapChainConfig* pConfig)
{
	HRESULT hr;

	IDXGIDevice1* pDXGIDevice;
	hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDXGIDevice);

	IDXGIAdapter1* pAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter1), (void **)&pAdapter);

	IDXGIFactory1* pFactory;
	pAdapter->GetParent(__uuidof(IDXGIFactory1), (void **)&pFactory);

	IDXGISwapChain* pSwapChain;	
	hr = pFactory->CreateSwapChain(m_pDevice, &pConfig->m_Desc, &pSwapChain);
	
	SAFE_RELEASE(pDXGIDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	ID3D11Texture2D *pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast< void** >(&pBackBuffer));

	m_vResources.Add(new MX11Texture2D(pBackBuffer));

	int ResourceID = m_vResources.Size() - 1 + RT_TEXTURE2D;
	MX11Texture2DConfig TextureConfig;
	pBackBuffer->GetDesc(&TextureConfig.m_Desc);

	ResourcePtr Proxy(new MX11ResourceProxy(ResourceID, &TextureConfig, this));

	m_vSwapChains.Add(new MX11SwapChain(pSwapChain, Proxy));


	/*
	// set the render target as the back buffer
	m_pContext->OMSetRenderTargets(1, &m_pRTView, NULL);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(800);
	viewport.Height = static_cast<float>(600);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_pContext->RSSetViewports(1, &viewport);
	*/


	return m_vSwapChains.Size() - 1;
}
//------------------------------------------------------------------------|
int MX11Renderer::CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc)
{
	int TYPE = ResourceID & 0xFF0000;
	int ID = ResourceID & 0x00FFFF;
	ID3D11Resource* pResource;

	if(m_vResources.InRange(ID))
	{
		pResource = m_vResources[ID]->GetResource();
	}

	if(pResource)
	{
		ID3D11RenderTargetView* pView = NULL;
		HRESULT hr = m_pDevice->CreateRenderTargetView(pResource, pDesc, &pView);

		if(SUCCEEDED(hr))
		{
			MX11RenderTargetView* pRTView = new MX11RenderTargetView(pView);
			m_vRenderTargetViews.Add(pRTView);

			return m_vRenderTargetViews.Size() - 1;
		}
	}


	return -1;
}
//------------------------------------------------------------------------|
int MX11Renderer::CreateViewPort(D3D11_VIEWPORT viewport)
{
	MX11ViewPort* pViewPort = new MX11ViewPort(viewport);
	m_vViewPorts.Add(pViewPort);

	return m_vViewPorts.Size() - 1;
}
//------------------------------------------------------------------------|
ResourcePtr MX11Renderer::GetSwapChainResource(int ID)
{
	if( ID >= 0 && ID < m_vSwapChains.Size())
	{
		return m_vSwapChains[ID]->m_Resource;
	}
	return ResourcePtr(new MX11ResourceProxy());
}
//------------------------------------------------------------------------|
MX11RenderTargetView* MX11Renderer::GetRenderTargetView(int ID)
{
	return m_vRenderTargetViews[ID];
}
//------------------------------------------------------------------------|
MX11ViewPort* MX11Renderer::GetViewPort(int ID)
{
	return m_vViewPorts[ID];
}