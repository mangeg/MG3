//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11DeptStencilView
	{
	public:
		MX11DeptStencilView( ID3D11DepthStencilView* pView );
		virtual ~MX11DeptStencilView();

	protected:
		ID3D11DepthStencilView*	m_pView;

		friend MX11PipelineManager;
	};
}