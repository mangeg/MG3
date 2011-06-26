//------------------------------------------------------------------------|
#include "MG3.h"
#include "MX11Renderer.h"
#include "ScriptConsole.h"
#include "StringTools.h"

#include "DXGIAdapter.h"
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
	m_pSwapchain = NULL;
}
//------------------------------------------------------------------------|
MX11Renderer::~MX11Renderer()
{
}
//------------------------------------------------------------------------|
bool MX11Renderer::Initialize()
{
	HRESULT hr;
	IDXGIFactory1* pFactory;
	
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory);	
	if(FAILED(hr))
	{
		return false;
	}

	IDXGIAdapter1* pAdapter;
	TArray<DXGIAdapter*> vAdapters;

	while(pFactory->EnumAdapters1(vAdapters.Size(), &pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGIAdapter* a = new DXGIAdapter(pAdapter);
		vAdapters.Add( a );
	}

	UINT CreateDeviceFlags = 0;
#ifdef _DEBUG
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	ID3D11DeviceContext* pContext = 0;
	D3D_FEATURE_LEVEL level[] = { D3D_FEATURE_LEVEL_11_0 };
	hr = D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		CreateDeviceFlags,
		level,
		1,
		D3D11_SDK_VERSION,
		&m_pDevice,
		0,
		&pContext);

	if(FAILED(hr))
	{
		return false;
	}

	for(int i = 0; i < vAdapters.Size(); i++)
		delete vAdapters[i];
	SAFE_RELEASE(pFactory);

	hr = m_pDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&m_pDebugger);
	if(FAILED(hr))
	{
		Shutdown();
		return false;
	}
	
	m_FeatureLevel = m_pDevice->GetFeatureLevel();

	return true;
}
//------------------------------------------------------------------------|
void MX11Renderer::Shutdown()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDebugger);
	SAFE_RELEASE(m_pSwapchain);
}
//------------------------------------------------------------------------|
MX11Renderer* MX11Renderer::Get()
{
	return m_spRenderer;
}