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

		void ClearBuffers(XMFLOAT4 color);

		void ClearRenderTargets();
		void BindRenderTarget(int index, ResourcePtr pRT);
		void ApplyRenderTargets();

		void SetViewPort(int ID);

	private:
		ID3D11DeviceContext*	m_pContext;

		MX11OutputMergerStage	m_OutputMergerStage;
	};
}