//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11OutputMergerStage.h"
#include "MX11VertexStage.h"
#include "MX11ResourceProxy.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class IParamaterManager;
	class MX11RenderParameter;

	class MX11ShaderStage;

	class MX11PipelineManager
	{
	public:
		MX11PipelineManager();
		~MX11PipelineManager();

		void SetDeviceContext(ID3D11DeviceContext* pDeviceContext);

		void ClearBuffers(XMFLOAT4 color, float depth = 1.0f, UINT stencil = 0);

		void ClearRenderTargets();
		void BindRenderTarget(int index, ResourcePtr pRT);
		void BindDeptTarget(ResourcePtr pDT);
		void ApplyRenderTargets();

		void BindCBufferParameter(ShaderType type, MX11RenderParameter* pParameter, UINT slot, IParamaterManager* pParamManager);

		void BindShader(ShaderType type, int ID, IParamaterManager* pParamManager);
		void UnbindShader(ShaderType type);
		void UnbindShader(int ID);

		void BindVertexBuffer(ResourcePtr resource, UINT stride, UINT offset);

		void ApplyPipelineResource();

		void SetViewPort(int ID);

		void SetRasterizerState(int ID);
		void SetInputLayout(int ID);

		D3D11_MAPPED_SUBRESOURCE MapResource(int index, UINT subResource, D3D11_MAP actions, UINT flags);
		void UnMapResource(int index, UINT subResource);

		ID3D11DeviceContext* GetContext() {return m_pContext;}

	private:
		ID3D11DeviceContext*	m_pContext;

		MX11VertexStage			VertexStage;

		MX11ShaderStage*		ShaderStages[NUM_SHADER_TYPES];

		MX11OutputMergerStage	m_OutputMergerStage;
	};
}