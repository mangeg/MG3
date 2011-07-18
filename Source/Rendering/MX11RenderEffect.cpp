//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11RenderEffect.h"
#include "MX11PipelineManager.h"
#include "IParameterManager.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11RenderEffect::MX11RenderEffect()
{
	m_iVertexShader = -1;
	m_iDomainShader = -1;
	m_iHullShader = -1;
	m_iGeometryShader = -1;
	m_iCumputeShader = -1;
	m_iPixelShader = -1;

	m_iBlendState = -1;
	m_iDepthStencilState = -1;
	m_iRasterizerState = -1;
	m_uStencilRef = 0;
}
//------------------------------------------------------------------------|
MX11RenderEffect::~MX11RenderEffect()
{
}
//------------------------------------------------------------------------|
void MX11RenderEffect::ApplyEffect(MX11PipelineManager* pPipeline, IParamaterManager* pParamManager)
{
	if(m_iBlendState)
	{
	}
	if(m_iDepthStencilState)
	{
	}
	if(m_iRasterizerState >= 0)
	{
		pPipeline->SetRasterizerState(m_iRasterizerState);
	}

	pPipeline->BindShader(SHADER_VERTEX, m_iVertexShader, pParamManager);
	pPipeline->BindShader(SHADER_PIXEL, m_iPixelShader, pParamManager);
}