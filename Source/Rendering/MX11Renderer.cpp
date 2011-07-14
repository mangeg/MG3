//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Renderer.h"

#include "MX11ViewPort.h"

#include "MX11RenderTargetView.h"
#include "MX11DeptStencilView.h"

#include "MX11SwapChainConfig.h"
#include "MX11Texture2DConfig.h"

#include "MX11ResourceProxy.h"
#include "MX11SwapChain.h"
#include "MX11Texture2D.h"

#include "DXGIAdapter.h"
#include "MX11PipelineManager.h"

#include "MX11VertexShader.h"
#include "MX11PixelShader.h"

#include "MX11RasterizerState.h"
#include "MX11InputLayout.h"

#include "MX11RasterizerStateConfig.h"

#include "StringTools.h"
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
		DXGIAdapter* a = MG_NEW DXGIAdapter(pAdapter);
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

	m_pPipeline = MG_NEW MX11PipelineManager();
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

	for(int i = 0; i < m_vViewPorts.Size(); i++)
		delete m_vViewPorts[i];
	for(int i = 0; i < m_vRenderTargetViews.Size(); i++)
		delete m_vRenderTargetViews[i];
	for(int i = 0; i < m_vDeptStencilViews.Size(); i++)
		delete m_vDeptStencilViews[i];
	for(int i = 0; i < m_vResources.Size(); i++)
		delete m_vResources[i];
	for(int i = 0; i < m_vShaders.Size(); i++)
		delete m_vShaders[i];
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
	hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast< void** >(&pDXGIDevice));

	IDXGIAdapter1* pAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter1), reinterpret_cast< void** >(&pAdapter));

	IDXGIFactory1* pFactory;
	pAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast< void** >(&pFactory));

	IDXGISwapChain* pSwapChain;	
	hr = pFactory->CreateSwapChain(m_pDevice, &pConfig->m_Desc, &pSwapChain);
	
	SAFE_RELEASE(pDXGIDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	ID3D11Texture2D *pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast< void** >(&pBackBuffer));

	m_vResources.Add(MG_NEW MX11Texture2D(pBackBuffer));

	int ResourceID = m_vResources.Size() - 1 + RT_TEXTURE2D;
	MX11Texture2DConfig TextureConfig;
	pBackBuffer->GetDesc(&TextureConfig.m_Desc);

	ResourcePtr Proxy(MG_NEW MX11ResourceProxy(ResourceID, &TextureConfig, this));

	m_vSwapChains.Add(MG_NEW MX11SwapChain(pSwapChain, Proxy));

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
			MX11RenderTargetView* pRTView = MG_NEW MX11RenderTargetView(pView);
			m_vRenderTargetViews.Add(pRTView);

			return m_vRenderTargetViews.Size() - 1;
		}
	}


	return -1;
}
//------------------------------------------------------------------------|
int MX11Renderer::CreateDeptStenchilView(int ResourceID, D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc)
{
	int TYPE = ResourceID & 0x00FF0000;
	int ID = ResourceID & 0x0000FFFF;
	ID3D11Resource* pResource = NULL;

	if(m_vResources.InRange(ID))
		pResource = m_vResources[ID]->GetResource();

	if(pResource)
	{
		ID3D11DepthStencilView* pView = NULL;
		HRESULT hr = m_pDevice->CreateDepthStencilView(pResource, pDesc, &pView);

		if(SUCCEEDED(hr))
		{
			MX11DeptStencilView* pDeptStencil = MG_NEW MX11DeptStencilView(pView);
			m_vDeptStencilViews.Add(pDeptStencil);

			return m_vDeptStencilViews.Size() - 1;
		}
	}

	return -1;
}
//------------------------------------------------------------------------|
int MX11Renderer::CreateViewPort(D3D11_VIEWPORT viewport)
{
	MX11ViewPort* pViewPort = MG_NEW MX11ViewPort(viewport);
	m_vViewPorts.Add(pViewPort);

	return m_vViewPorts.Size() - 1;
}
//------------------------------------------------------------------------|
int MX11Renderer::LoadShader(ShaderType type, std::wstring const& file, std::wstring const& entry, std::wstring const& profile)
{
	HRESULT hr;

	ID3DBlob* pCompiledShader;
	ID3DBlob* pCompileErrors;

	char AsciiEntry[1024];
	char AsciiModel[1024];
	WideCharToMultiByte(CP_ACP, 0, entry.c_str(), -1, AsciiEntry, 1024, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, profile.c_str(), -1, AsciiModel, 1024, NULL, NULL);
	
	UINT flags = D3D10_SHADER_PACK_MATRIX_ROW_MAJOR;
#ifdef _DEBUG
	flags |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION | D3D10_SHADER_WARNINGS_ARE_ERRORS;
#endif

	if(FAILED(hr = D3DX11CompileFromFile(
		file.c_str(), 
		NULL, 
		NULL, 
		AsciiEntry, 
		AsciiModel, 
		flags, 
		0, 
		NULL, 
		&pCompiledShader, 
		&pCompileErrors, 
		&hr)))
	{
		std::wstringstream s;
		s << L"Error compiling shader: " << file << std::endl;
		s << L"Errors:" << std::endl;
		if(pCompileErrors)
		{
			const char* pMessage = (const char*)pCompileErrors->GetBufferPointer();
			s << StringTools::ToUnicode(std::string(pMessage));
			Log::Get() << s.str() << Flush;
		}

		return -1;
	}

	MX11Shader* pShader;
	switch(type)
	{
	case SHADER_VERTEX:
		{
			ID3D11VertexShader* pVertexShader = NULL;
			hr = m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), 0, &pVertexShader);
			pShader = new MX11VertexShader(pVertexShader);
			break;
		}
	case SHADER_PIXEL:
		{
			ID3D11PixelShader* pPixelShader = NULL;
			hr = m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), 0, &pPixelShader);
			pShader = new MX11PixelShader(pPixelShader);
			break;
		}
	}

	pShader->m_pCompiledShader = pCompiledShader;

	m_vShaders.Add(pShader);

	return m_vShaders.Size() - 1;
}
//------------------------------------------------------------------------|
ResourcePtr MX11Renderer::CreateTexture2D(MX11Texture2DConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData)
{
	ID3D11Texture2D* pTexture = NULL;
	HRESULT hr = m_pDevice->CreateTexture2D(&pConfig->m_Desc, pData, &pTexture);
	if(SUCCEEDED(hr))
	{
		MX11Texture2D* pTex = MG_NEW MX11Texture2D(pTexture);
		pTex->SetDesiredDescription(pConfig->GetTextureDesc());
		m_vResources.Add(pTex);

		int ResourceID = (m_vResources.Size() - 1) + RT_TEXTURE2D;
		ResourcePtr Proxy(MG_NEW MX11ResourceProxy(ResourceID, pConfig, this));
		return Proxy;
	}

	return ResourcePtr(MG_NEW MX11ResourceProxy());
}
//------------------------------------------------------------------------|
ResourcePtr MX11Renderer::GetSwapChainResource(int ID)
{
	if( ID >= 0 && ID < m_vSwapChains.Size())
	{
		return m_vSwapChains[ID]->m_Resource;
	}
	return ResourcePtr(MG_NEW MX11ResourceProxy());
}
//------------------------------------------------------------------------|
MX11RenderTargetView* MX11Renderer::GetRenderTargetView(int ID)
{
	return m_vRenderTargetViews[ID];
}
//------------------------------------------------------------------------|
MX11DeptStencilView* MX11Renderer::GetDeptStencilView(int ID)
{
	return m_vDeptStencilViews[ID];
}
//------------------------------------------------------------------------|
MX11ViewPort* MX11Renderer::GetViewPort(int ID)
{
	return m_vViewPorts[ID];
}
//------------------------------------------------------------------------|
MX11Shader* MX11Renderer::GetShader(int ID)
{
	return m_vShaders[ID];
}
//------------------------------------------------------------------------|
int MX11Renderer::CreateRasterizerState(MX11RasterizerStateConfig* pConfig)
{
	ID3D11RasterizerState* pState = NULL;

	HRESULT hr = m_pDevice->CreateRasterizerState(pConfig, &pState);
	if(FAILED(hr))
	{
		Log::Get() << L"Failed to create rasterizer state." << Flush;
		return -1;
	}

	boost::shared_ptr<MX11RasterizerState> ptr(MG_NEW MX11RasterizerState(pState));
	m_vRasterizerStates.Add(ptr);

	return m_vRasterizerStates.Size() - 1;
}
//------------------------------------------------------------------------|
int MX11Renderer::CreateInputLayout(TArray<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID)
{
	D3D11_INPUT_ELEMENT_DESC* pElements = MG_NEW D3D11_INPUT_ELEMENT_DESC[elements.Size()];
	for(int i = 0; i < elements.Size(); i++)
		pElements[i] = elements[i];

	ID3DBlob* pCompiledShader = m_vShaders[ShaderID]->m_pCompiledShader;
	ID3D11InputLayout* pLayout = NULL;

	HRESULT hr = m_pDevice->CreateInputLayout(pElements, elements.Size(), 
		pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &pLayout);

	SAFE_DELETE_ARRAY(pElements);

	if(FAILED(hr))
	{
		Log::Get() << L"Failed to create input layout for shader " << ShaderID << L"." << Flush;
		return -1;
	}

	boost::shared_ptr<MX11InputLayout> w(MG_NEW MX11InputLayout(pLayout));
	m_vInputLayouts.Add(w);

	return m_vInputLayouts.Size() - 1;
}
//------------------------------------------------------------------------|
boost::shared_ptr<MX11RasterizerState> MX11Renderer::GetRasterizerState(int ID)
{
	return m_vRasterizerStates[ID];
}
//------------------------------------------------------------------------|
boost::shared_ptr<MX11InputLayout> MX11Renderer::GetInputLayout(int ID)
{
	return m_vInputLayouts[ID];
}