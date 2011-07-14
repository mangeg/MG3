//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11DeptStencilViewConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11DeptStencilViewConfig::MX11DeptStencilViewConfig()
{
	SetDefaults();
}
//------------------------------------------------------------------------|
MX11DeptStencilViewConfig::~MX11DeptStencilViewConfig()
{
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetDefaults()
{
	// Set the state to the default configuration.  These are the D3D11 default
	// values as well.

	m_Desc.Flags = 0;
	m_Desc.Format = DXGI_FORMAT_UNKNOWN;
	m_Desc.ViewDimension = D3D11_DSV_DIMENSION_UNKNOWN;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetFormat( DXGI_FORMAT state )
{
	m_Desc.Format = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetViewDimensions( D3D11_DSV_DIMENSION state )
{
	m_Desc.ViewDimension = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetFlags( UINT state )
{
	m_Desc.Flags = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetTexture1D( D3D11_TEX1D_DSV state )
{
	m_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1D;
	m_Desc.Texture1D = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetTexture1DArray( D3D11_TEX1D_ARRAY_DSV state )
{
	m_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE1DARRAY;
	m_Desc.Texture1DArray = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetTexture2D( D3D11_TEX2D_DSV state )
{
	m_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	m_Desc.Texture2D = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetTexture2DArray( D3D11_TEX2D_ARRAY_DSV state )
{
	m_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
	m_Desc.Texture2DArray = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetTexture2DMS( D3D11_TEX2DMS_DSV state )
{
	m_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	m_Desc.Texture2DMS = state;
}
//------------------------------------------------------------------------|
void MX11DeptStencilViewConfig::SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_DSV state )
{
	m_Desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
	m_Desc.Texture2DMSArray = state;
}
//------------------------------------------------------------------------|
D3D11_DEPTH_STENCIL_VIEW_DESC& MX11DeptStencilViewConfig::GetDSVDesc()
{
	return m_Desc;
}
//------------------------------------------------------------------------|