//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11PipelineManager.h"
#include "MX11RenderTargetView.h"
#include "MX11DeptStencilView.h"
#include "MX11ViewPort.h"
#include "MX11Shader.h"
#include "MX11VertexShader.h"
#include "MX11PixelShader.h"

#include "MX11RasterizerState.h"
#include "MX11InputLayout.h"
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
void MX11PipelineManager::BindShader(ShaderType type, int ID)
{
	MX11Renderer* pRenderer = MX11Renderer::Get();
	MX11Shader* pShader = pRenderer->GetShader(ID);

	if(pShader)
	{
		if(pShader->GetType() == type)
		{
			switch(type)
			{
			case SHADER_VERTEX:
				{
					ID3D11VertexShader* pVertexShader = reinterpret_cast<MX11VertexShader*>(pShader)->m_pVertexShader;
					m_pContext->VSSetShader(pVertexShader, NULL, 0);
					break;
				}
			case SHADER_PIXEL:
				{
					ID3D11PixelShader* pPixelShader = reinterpret_cast<MX11PixelShader*>(pShader)->m_pPixelShader;
					m_pContext->PSSetShader(pPixelShader, NULL, 0);
					break;
				}
			}
			
		}
		else
		{
			Log::Get() << L"Shader ID " << ID << L" is not of type " << type << L"." << Flush;
		}
	}
	else
	{
		if(ID == -1)
		{
			UnbindShader(type);
		}
		else
		{
			Log::Get() << L"Invalid shader ID: " << ID << Flush; 
		}
	}
}
//------------------------------------------------------------------------|
void MX11PipelineManager::UnbindShader(ShaderType type)
{
	switch(type)
	{
	case SHADER_VERTEX:
		m_pContext->VSSetShader(NULL, NULL, 0);
		break;
	case SHADER_PIXEL:
		m_pContext->PSSetShader(NULL, NULL, 0);
		break;
	}
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
//------------------------------------------------------------------------|
void MX11PipelineManager::SetRasterizerState(int ID)
{
	MX11Renderer* pRenderer = MX11Renderer::Get();
	
	ID3D11RasterizerState* pState = pRenderer->GetRasterizerState(ID)->m_pState;

	if(pState)
	{
		m_pContext->RSSetState(pState);
	}
	else
		Log::Get() << L"Attempted to set an invalid Rasterizer State ID." << Flush;
}
//------------------------------------------------------------------------|
void MX11PipelineManager::SetInputLayout(int ID)
{
	MX11Renderer* pRenderer = MX11Renderer::Get();
	ID3D11InputLayout* pLayout = pRenderer->GetInputLayout(ID)->m_pLayout;

	if(pLayout)
	{
		m_pContext->IASetInputLayout(pLayout);
	}
	else
	{
		Log::Get() << L"Trying to set invalid input layout " << ID << L"." << Flush;
	}
}