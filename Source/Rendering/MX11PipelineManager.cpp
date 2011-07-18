//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Renderer.h"
#include "IMX11Resource.h"
#include "MX11PipelineManager.h"
#include "MX11RenderTargetView.h"
#include "MX11DeptStencilView.h"
#include "MX11ViewPort.h"
#include "MX11Shader.h"
#include "MX11VertexShader.h"
#include "MX11PixelShader.h"

#include "MX11RasterizerState.h"
#include "MX11InputLayout.h"

#include "IParameterManager.h"
#include "MX11RenderParameter.h"
#include "MX11ConstantBufferParameter.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11PipelineManager::MX11PipelineManager()
	: m_pContext(NULL)
{
	ShaderStages[SHADER_VERTEX] = &VertexStage;
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
void MX11PipelineManager::BindCBufferParameter(ShaderType type,
	MX11RenderParameter* pParameter, UINT slot, IParamaterManager* pParamManager)
{
	MX11Renderer* pRenderer = MX11Renderer::Get();

	if(pParameter->GetParameterType() == CBUFFER)
	{
		MX11ConstantBufferParameter* pCBuffer = static_cast<MX11ConstantBufferParameter*>(pParameter);
		int ID = pCBuffer->GetIndex() & 0xffff;

		IMX11Resource* pResource = pRenderer->GetResource(ID);

		if( pResource || ID == -1)
		{
			ID3D11Buffer* pBuffer = NULL;

			if(ID >= 0)
				pBuffer = static_cast<ID3D11Buffer*>(pResource->GetResource());

			ShaderStages[type]->SetCBuffer(slot, pBuffer);
		}
	}
}
//------------------------------------------------------------------------|
void MX11PipelineManager::BindShader(ShaderType type, int ID, IParamaterManager* pParamManager)
{
	MX11Renderer* pRenderer = MX11Renderer::Get();
	MX11Shader* pShader = pRenderer->GetShader(ID);

	if(pShader)
	{
		pShader->UpdateParameters(this, pParamManager);

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
			
			pShader->BindParameters(this, pParamManager);
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
void MX11PipelineManager::BindVertexBuffer(ResourcePtr resource, UINT stride, UINT offset)
{
	int index = resource->m_iResource;

	int TYPE = index & 0x00FF0000;
	int ID = index & 0x0000FFFF;

	MX11Renderer* pRenderer = MX11Renderer::Get();
	ID3D11Buffer* pBuffer = static_cast<ID3D11Buffer*>(pRenderer->GetResource(ID)->GetResource());

	ID3D11Buffer* pBuffers[] = {pBuffer};
	UINT Strides[] = {stride};
	UINT Offsets[] = {offset};

	if(pBuffer)
	{
		m_pContext->IASetVertexBuffers(0, 1, pBuffers, Strides, Offsets);
	}
	else
	{
		Log::Get() << L"Tried to bind invalid vertex buffer " << ID << L"." << Flush;
	}
}
//------------------------------------------------------------------------|
void MX11PipelineManager::ApplyPipelineResource()
{
	/*
	for(UINT i = 0; i < NUM_SHADER_TYPES; i++)
	{
		ShaderStages[i]->BindResources(m_pContext);
	}
	*/
	VertexStage.BindResources(m_pContext);
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
//------------------------------------------------------------------------|
D3D11_MAPPED_SUBRESOURCE MX11PipelineManager::MapResource(int index, UINT subResource, D3D11_MAP actions, UINT flags)
{
	int ID = index & 0X0000FFFF;

	ID3D11Resource* pResource = NULL;
	D3D11_MAPPED_SUBRESOURCE Data;

	pResource = MX11Renderer::Get()->GetResource(ID)->GetResource();

	HRESULT hr = m_pContext->Map(pResource, subResource, actions, flags, &Data);

	if(FAILED(hr))
		Log::Get() << L"Failed to map resource." << Flush;

	return Data;
}
//------------------------------------------------------------------------|
void MX11PipelineManager::UnMapResource(int index, UINT subResource)
{
	int ID = index & 0X0000FFFF;

	ID3D11Resource* pResource = NULL;

	pResource = MX11Renderer::Get()->GetResource(ID)->GetResource();

	m_pContext->Unmap(pResource, subResource);
}