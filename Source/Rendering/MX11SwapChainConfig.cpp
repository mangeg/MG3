//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11SwapChainConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11SwapChainConfig::MX11SwapChainConfig()
{
	SetDefault();
}
//------------------------------------------------------------------------|
MX11SwapChainConfig::~MX11SwapChainConfig()
{
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetDefault()
{
	m_Desc.BufferDesc.Width = 1;
	m_Desc.BufferDesc.Height = 1;
	m_Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	m_Desc.BufferDesc.RefreshRate.Numerator = 60;
	m_Desc.BufferDesc.RefreshRate.Denominator = 1;

	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;

	m_Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_Desc.BufferCount = 2;
	m_Desc.OutputWindow = 0;
	m_Desc.Windowed = true;
	m_Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	m_Desc.Flags = 0;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetWidth( UINT width )
{
	m_Desc.BufferDesc.Width = width;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetHeight( UINT height )
{
	m_Desc.BufferDesc.Height = height;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetRefreshRateNumerator( UINT numerator )
{
	m_Desc.BufferDesc.RefreshRate.Numerator = numerator;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetRefreshRateDenominator( UINT denominator )
{
	m_Desc.BufferDesc.RefreshRate.Denominator = denominator;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetFormat( DXGI_FORMAT Format )
{
	m_Desc.BufferDesc.Format = Format;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetScanlineOrder( DXGI_MODE_SCANLINE_ORDER ScanlineOrdering )
{
	m_Desc.BufferDesc.ScanlineOrdering = ScanlineOrdering;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetScaling( DXGI_MODE_SCALING Scaling )
{
	m_Desc.BufferDesc.Scaling = Scaling;
}

//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetBufferDesc( DXGI_MODE_DESC BufferDesc )
{
	m_Desc.BufferDesc = BufferDesc;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetSampleDesc( DXGI_SAMPLE_DESC SampleDesc )
{
	m_Desc.SampleDesc = SampleDesc;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetBufferUsage( DXGI_USAGE BufferUsage )
{
	m_Desc.BufferUsage = BufferUsage;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetBufferCount( UINT BufferCount )
{
	m_Desc.BufferCount = BufferCount;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetOutputWindow( HWND OutputWindow )
{
	m_Desc.OutputWindow = OutputWindow;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetWindowed( bool Windowed )
{
	m_Desc.Windowed = Windowed;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetSwapEffect( DXGI_SWAP_EFFECT SwapEffect )
{
	m_Desc.SwapEffect = SwapEffect;
}
//------------------------------------------------------------------------|
void MX11SwapChainConfig::SetFlags( UINT Flags )
{
	m_Desc.Flags = Flags;
}
//------------------------------------------------------------------------|
DXGI_SWAP_CHAIN_DESC MX11SwapChainConfig::GetSwapChainDesc()
{
	return m_Desc;
}