//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MG3.h"
#include "TArray.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Renderer
	{
	public:
		MX11Renderer();
		~MX11Renderer();

		static MX11Renderer*	Get();

		bool	Initialize();
		void	Shutdown();

	protected:
		ID3D11Device*	m_pDevice;
		ID3D11Debug*	m_pDebugger;

		IDXGISwapChain*	m_pSwapchain;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		static MX11Renderer*	m_spRenderer;
	};
}