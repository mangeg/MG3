//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
namespace MG3
{
	class IParamaterManager;
	class MX11PipelineManager;

	class MX11RenderEffect
	{
	public:
		MX11RenderEffect();
		virtual ~MX11RenderEffect();

		void ApplyEffect(MX11PipelineManager* pPipeline, IParamaterManager* pParamManager);

	public:
		int	m_iVertexShader;
		int	m_iHullShader;
		int	m_iDomainShader;
		int m_iGeometryShader;
		int	m_iCumputeShader;
		int	m_iPixelShader;

		int	m_iBlendState;
		int	m_iDepthStencilState;
		int	m_iRasterizerState;
		UINT	m_uStencilRef;		
	};
}