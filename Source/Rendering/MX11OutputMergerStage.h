//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11OutputMergerStage
	{
	public:
		MX11OutputMergerStage();
		virtual ~MX11OutputMergerStage();

		void SetRenderTargetView(int index, ID3D11RenderTargetView* pRTView);

		void BindResource(ID3D11DeviceContext* pContext);
		void ClearResources(ID3D11DeviceContext* pContext);
		void UnbindResources(ID3D11DeviceContext* pContext);

	protected:
		friend MX11PipelineManager;

		ID3D11RenderTargetView*	m_vRenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
		ID3D11RenderTargetView*	m_vActiveRenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	};
}