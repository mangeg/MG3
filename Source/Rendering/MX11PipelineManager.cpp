//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11PipelineManager.h"
#include "MX11RenderTargetView.h"
#include "MX11DeptStencilView.h"
#include "MX11ViewPort.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11PipelineManager::MX11PipelineManager()
	: m_pContext(NULL)
{
}
//------------------------------------------------------------------------|
MX11PipelineManager::~MX11PipelineManager()
{
	if(m_pContext) 
	{
		m_pContext->ClearState();
	}

	SAFE_RELEASE(m_pContext);
}
//------------------------------------------------------------------------|
void MX11PipelineManager::SetDeviceContext(ID3D11DeviceContext* pDeviceContext)
{
	m_pContext = pDeviceContext;
}
//------------------------------------------------------------------------|
void MX11PipelineManager::ClearBuffers(XMFLOAT4 color, float depth, UINT stencil)
{
	for(int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
	{
		if(m_OutputMergerStage.m_vActiveRenderTargetViews[i])
		{
			float clearColor [] = {color.x, color.y, color.z, color.w};
			m_pContext->ClearRenderTargetView(m_OutputMergerStage.m_vActiveRenderTargetViews[i], clearColor);
		}
	}

	if(m_OutputMergerStage.m_pActiveDeptStencilView)
	{
		m_pContext->ClearDepthStencilView(m_OutputMergerStage.m_pActiveDeptStencilView, D3D11_CLEAR_DEPTH, depth, stencil );
	}
}
//------------------------------------------------------------------------|
void MX11PipelineManager::BindRenderTarget( int index, ResourcePtr RenderTarget )
{
	MX11RenderTargetView* pView = MX11Renderer::Get()->GetRenderTargetView( RenderTarget->m_iRTVResource );

	if (pView)
	{
		ID3D11RenderTargetView* pRenderTarget = {pView->m_pRTView};
		m_OutputMergerStage.SetRenderTargetView( index, pRenderTarget );
	}	
	else
		Log::Get() << L"Tried to bind an invalid render target view!";

}
//------------------------------------------------------------------------|
void MX11PipelineManager::BindDeptTarget(ResourcePtr DeptTarget)
{
	int ResourceID = DeptTarget->m_iResource;
	MX11Renderer* pRenderr = MX11Renderer::Get();
	MX11DeptStencilView* pView = pRenderr->GetDeptStencilView(ResourceID);

	if(pView)
	{
		ID3D11DepthStencilView* pDeptStencilView = pView->m_pView;
		m_OutputMergerStage.SetDeptStencilView(pDeptStencilView);
	}
}
//------------------------------------------------------------------------|
void MX11PipelineManager::ClearRenderTargets()
{
	m_OutputMergerStage.ClearResources(m_pContext);
}
//------------------------------------------------------------------------|
void MX11PipelineManager::ApplyRenderTargets( )
{
	m_OutputMergerStage.BindResource(m_pContext);
}
//------------------------------------------------------------------------|
void MX11PipelineManager::SetViewPort(int ID)
{
	MX11ViewPort* pViewPort = MX11Renderer::Get()->GetViewPort(ID);
	if(pViewPort)
	{
		m_pContext->RSSetViewports(1, &pViewPort->m_Desc);
	}
}