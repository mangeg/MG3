//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11ResourceView.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11RenderTargetView : public MX11ResourceView
	{
	public:
		MX11RenderTargetView(ID3D11RenderTargetView* pRTView);
		virtual ~MX11RenderTargetView();
	protected:
		ID3D11RenderTargetView*	m_pRTView;

		friend MX11PipelineManager;
	};
}