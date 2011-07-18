//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11ResourceProxy.h"
#include "MX11Renderer.h"
#include "MX11Texture2DConfig.h"
#include "MX11RenderTargetViewConfig.h"
#include "MX11DeptStencilViewConfig.h"
#include "MX11BufferConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11ResourceProxy::MX11ResourceProxy()
{
	m_iResource = m_iRTVResource = -1;

	m_pBufferConfig = NULL;
	m_pTexture2DConfig = NULL;
	m_pRTVConfig = NULL;
}
//------------------------------------------------------------------------|
MX11ResourceProxy::MX11ResourceProxy(int ResourceID, MX11BufferConfig* pConfig, MX11Renderer* pRenderer,
	MX11RenderTargetViewConfig* pRTVConfig,
	MX11DeptStencilViewConfig* pDSVConfig)
{
	D3D11_BUFFER_DESC desc = pConfig->GetBufferDesc();
	_Initialize(desc.BindFlags, ResourceID, pRenderer,
		pRTVConfig,
		pDSVConfig);

	m_pBufferConfig = NULL;
	m_pBufferConfig = MG_NEW MX11BufferConfig();
	*m_pBufferConfig = *pConfig;
}
//------------------------------------------------------------------------|
MX11ResourceProxy::MX11ResourceProxy(int ResourceID, MX11Texture2DConfig* pConfig, MX11Renderer* pRenderer,
	MX11RenderTargetViewConfig* pRTVConfig,
	MX11DeptStencilViewConfig* pDSVConfig)
{
	D3D11_TEXTURE2D_DESC desc = pConfig->GetTextureDesc();
	_Initialize(desc.BindFlags, ResourceID, pRenderer
		,pRTVConfig,
		pDSVConfig);

	m_pTexture2DConfig = NULL;
	m_pTexture2DConfig = MG_NEW MX11Texture2DConfig();
	*m_pTexture2DConfig = *pConfig;
}
//------------------------------------------------------------------------|
MX11ResourceProxy::~MX11ResourceProxy()
{
	SAFE_DELETE(m_pBufferConfig);
	SAFE_DELETE(m_pTexture2DConfig);
	SAFE_DELETE(m_pRTVConfig);
}
//------------------------------------------------------------------------|
void MX11ResourceProxy::_Initialize(UINT BindFlags, int ResourceID, MX11Renderer* pRenderer, 
	MX11RenderTargetViewConfig* pRTVConfig,
	MX11DeptStencilViewConfig* pDSVConfig)
{
	m_iResource = ResourceID;

	m_pBufferConfig = NULL;
	m_pTexture2DConfig = NULL;
	m_pRTVConfig = NULL;
	m_pDSVConfig = NULL;

	if(pRTVConfig)
	{
		m_pRTVConfig = MG_NEW MX11RenderTargetViewConfig();
		*m_pRTVConfig = *pRTVConfig;
	}
	if(pDSVConfig)
	{
		m_pDSVConfig = MG_NEW MX11DeptStencilViewConfig();
		*m_pDSVConfig = *pDSVConfig;
	}

	if((BindFlags & D3D11_BIND_RENDER_TARGET) == D3D11_BIND_RENDER_TARGET)
	{
		D3D11_RENDER_TARGET_VIEW_DESC* pDesc = pRTVConfig ? &pRTVConfig->GetRTVDesc() : NULL;
		m_iRTVResource = pRenderer->CreateRenderTargetView(m_iResource, pDesc);
	}
	if((BindFlags & D3D11_BIND_DEPTH_STENCIL) == D3D11_BIND_DEPTH_STENCIL)
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc = m_pDSVConfig ? &pDSVConfig->GetDSVDesc() : NULL;
		m_iDSVResource = pRenderer->CreateDeptStenchilView(ResourceID, pDesc);
	}
}