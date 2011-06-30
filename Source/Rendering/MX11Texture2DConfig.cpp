//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Texture2DConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11Texture2DConfig::MX11Texture2DConfig()
{
	SetDefaults();
}
//------------------------------------------------------------------------|
MX11Texture2DConfig::~MX11Texture2DConfig()
{
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetDefaults()
{
	// Set the state to the default configuration.  These are the D3D11 default
	// values as well.

	m_Desc.Width = 1;
	m_Desc.Height = 1;
	m_Desc.MipLevels = 1;
	m_Desc.ArraySize = 1;
	m_Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;
	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m_Desc.CPUAccessFlags = 0;
	m_Desc.MiscFlags = 0;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetDepthBuffer(UINT width, UINT height)
{
	m_Desc.Width = width;
	m_Desc.Height = height;
	m_Desc.MipLevels = 1;
	m_Desc.ArraySize = 1;
	m_Desc.Format = DXGI_FORMAT_D32_FLOAT;
	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;
	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_Desc.CPUAccessFlags = 0;
	m_Desc.MiscFlags = 0;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetColorBuffer(UINT width, UINT height)
{
	m_Desc.Width = width;
	m_Desc.Height = height;
	m_Desc.MipLevels = 1;
	m_Desc.ArraySize = 1;
	m_Desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;
	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m_Desc.CPUAccessFlags = 0;
	m_Desc.MiscFlags = 0;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetWidth( UINT state )
{
	m_Desc.Width = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetHeight( UINT state )
{
	m_Desc.Height = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetMipLevels( UINT state )
{
	m_Desc.MipLevels = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetArraySize( UINT state )
{
	m_Desc.ArraySize = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetFormat( DXGI_FORMAT state )
{
	m_Desc.Format = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetSampleDesc( DXGI_SAMPLE_DESC state )
{
	m_Desc.SampleDesc = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetUsage( D3D11_USAGE state ) 
{
	m_Desc.Usage = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetBindFlags( UINT state )
{
	m_Desc.BindFlags = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetCPUAccessFlags( UINT state )
{
	m_Desc.CPUAccessFlags = state;
}
//------------------------------------------------------------------------|
void MX11Texture2DConfig::SetMiscFlags( UINT state )
{
	m_Desc.MiscFlags = state;
}
//------------------------------------------------------------------------|
D3D11_TEXTURE2D_DESC MX11Texture2DConfig::GetTextureDesc()
{
	return m_Desc;
}