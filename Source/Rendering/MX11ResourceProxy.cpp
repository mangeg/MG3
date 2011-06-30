//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11ResourceProxy.h"
#include "MX11Renderer.h"
#include "MX11Texture2DConfig.h"
#include "MX11RenderTargetViewConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11ResourceProxy::MX11ResourceProxy()
{
	m_iResource = m_iRTVResource = -1;

	m_pTexture2DConfig = NULL;

	m_pRTVConfig = NULL;
}
//------------------------------------------------------------------------|
MX11ResourceProxy::MX11ResourceProxy(int ResourceID, MX11Texture2DConfig* pConfig, MX11Renderer* pRenderer,
	MX11RenderTargetViewConfig* pRTVConfig)
{
	D3D11_TEXTURE2D_DESC desc = pConfig->GetTextureDesc();
	_Initialize(desc.BindFlags, ResourceID, pRenderer
		, pRTVConfig);

	m_pTexture2DConfig = new MX11Texture2DConfig();
	*m_pTexture2DConfig = *pConfig;
}
//------------------------------------------------------------------------|
MX11ResourceProxy::~MX11ResourceProxy()
{
	SAFE_DELETE(m_pTexture2DConfig);

	SAFE_DELETE(m_pRTVConfig);
}
//------------------------------------------------------------------------|
void MX11ResourceProxy::_Initialize(UINT BindFlags, int ResourceID, MX11Renderer* pRenderer, 
	MX11RenderTargetViewConfig* pRTVConfig)
{
	m_iResource = ResourceID;

	m_pRTVConfig = NULL;

	if(pRTVConfig)
	{
		m_pRTVConfig = new MX11RenderTargetViewConfig();
		*m_pRTVConfig = *pRTVConfig;
	}

	if((BindFlags & D3D11_BIND_RENDER_TARGET) == D3D11_BIND_RENDER_TARGET)
	{
		D3D11_RENDER_TARGET_VIEW_DESC* pDesc = pRTVConfig ? &pRTVConfig->GetRTVDesc() : NULL;
		m_iRTVResource = pRenderer->CreateRenderTargetView(m_iResource, pDesc);
	}
}