//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11RenderTargetViewConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11RenderTargetViewConfig::MX11RenderTargetViewConfig()
{
	SetDefaults();
}
//------------------------------------------------------------------------|
MX11RenderTargetViewConfig::~MX11RenderTargetViewConfig()
{
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetDefaults()
{
	// Set the state to the default configuration.  These are the D3D11 default
	// values as well.

	m_Desc.Format = DXGI_FORMAT_UNKNOWN;
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_UNKNOWN;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetFormat( DXGI_FORMAT state )
{
	m_Desc.Format = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetViewDimensions( D3D11_RTV_DIMENSION state )
{
	m_Desc.ViewDimension = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetBuffer( D3D11_BUFFER_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_BUFFER;
	m_Desc.Buffer = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetTexture1D( D3D11_TEX1D_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
	m_Desc.Texture1D = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetTexture1DArray( D3D11_TEX1D_ARRAY_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
	m_Desc.Texture1DArray = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetTexture2D( D3D11_TEX2D_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	m_Desc.Texture2D = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetTexture2DArray( D3D11_TEX2D_ARRAY_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	m_Desc.Texture2DArray = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetTexture2DMS( D3D11_TEX2DMS_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	m_Desc.Texture2DMS = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
	m_Desc.Texture2DMSArray = state;
}
//------------------------------------------------------------------------|
void MX11RenderTargetViewConfig::SetTexture3D( D3D11_TEX3D_RTV state )
{
	m_Desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
	m_Desc.Texture3D = state;
}
//------------------------------------------------------------------------|
D3D11_RENDER_TARGET_VIEW_DESC& MX11RenderTargetViewConfig::GetRTVDesc()
{
	return m_Desc;
}