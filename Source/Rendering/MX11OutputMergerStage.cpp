//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11OutputMergerStage.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11OutputMergerStage::MX11OutputMergerStage()
{
	ZeroMemory(m_vRenderTargetViews, sizeof(m_vRenderTargetViews[0]) * D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);
	ZeroMemory(m_vActiveRenderTargetViews, sizeof(m_vActiveRenderTargetViews[0]) * D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);
	m_pDeptStencilView = NULL;
	m_pActiveDeptStencilView = NULL;
}
//------------------------------------------------------------------------|
MX11OutputMergerStage::~MX11OutputMergerStage()
{
}
//------------------------------------------------------------------------|
void MX11OutputMergerStage::SetRenderTargetView(int index, ID3D11RenderTargetView* pRTView)
{
	if(index >= 0 && index < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
	{
		m_vRenderTargetViews[index] = pRTView;
	}
}
//------------------------------------------------------------------------|
void MX11OutputMergerStage::SetDeptStencilView(ID3D11DepthStencilView* pDSView)
{
	m_pDeptStencilView = pDSView;
}
//------------------------------------------------------------------------|
void MX11OutputMergerStage::BindResource(ID3D11DeviceContext* pContext)
{
	int iChanged = 0;
	for(int i = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT - 1; i >= 0; i--)
	{
		if(m_vRenderTargetViews[i] != m_vActiveRenderTargetViews[i])
		{
			iChanged++;
		}
	}

	if(m_pDeptStencilView != m_pActiveDeptStencilView)
		iChanged++;

	if(iChanged > 0)
	{
		pContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT - 1, m_vRenderTargetViews, m_pDeptStencilView);
	}

	for ( int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++ )
		m_vActiveRenderTargetViews[i] = m_vRenderTargetViews[i];
}
//------------------------------------------------------------------------|
void MX11OutputMergerStage::ClearResources(ID3D11DeviceContext* pContext)
{
	ZeroMemory(m_vRenderTargetViews, sizeof(m_vRenderTargetViews[0]) * D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);
}
//------------------------------------------------------------------------|
void MX11OutputMergerStage::UnbindResources(ID3D11DeviceContext* pContext)
{
	ClearResources(pContext);
	BindResource(pContext);
}
