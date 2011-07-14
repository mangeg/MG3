//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{

	class MX11RasterizerState
	{
	public:
		MX11RasterizerState(ID3D11RasterizerState* pState);
		virtual ~MX11RasterizerState();

	protected:
		ID3D11RasterizerState*	m_pState;

		friend MX11PipelineManager;
	};
}