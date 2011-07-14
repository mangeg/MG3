//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11OutputMergerStage.h"
#include "MX11ResourceProxy.h"
//------------------------------------------------------------------------|
namespace MG3
{
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

		void BindShader(ShaderType type, int ID);
		void UnbindShader(ShaderType type);
		void UnbindShader(int ID);

		void SetViewPort(int ID);

		void SetRasterizerState(int ID);
		void SetInputLayout(int ID);

		ID3D11DeviceContext* GetContext() {return m_pContext;}

	private:
		ID3D11DeviceContext*	m_pContext;

		MX11OutputMergerStage	m_OutputMergerStage;
	};
}