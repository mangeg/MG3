//------------------------------------------------------------------------|
//#pragma once
#ifndef MX11Renderer_H
#define MX11Renderer_H
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "TArray.h"
#include "MX11ResourceProxy.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11ViewPort;

	// Resources
	class MX11SwapChain;
	class MX11Texture2D;

	// Configs
	class MX11SwapChainConfig;
	class MX11Texture2DConfig;

	class MX11RenderTargetView;

	class MX11PipelineManager;

	class IMX11Resource;

	enum ResourceType
	{
		RT_VERTEXBUFFER = 0x010000,
		RT_INDEXBUFFER = 0x020000,
		RT_CONSTANTBUFFER = 0x030000,
		RT_STRUCTUREDBUFFER = 0x040000,
		RT_BYTEADDRESSBUFFER = 0x050000,
		RT_INDIRECTARGSBUFFER = 0x060000,
		RT_TEXTURE1D = 0x070000,
		RT_TEXTURE2D = 0x080000,
		RT_TEXTURE3D = 0x090000
	};	

	class MX11Renderer
	{
	public:
		MX11Renderer();
		~MX11Renderer();

		static MX11Renderer*	Get();

		virtual bool	Initialize();
		virtual void	Shutdown();
		
		int	CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc);

		virtual void	Present(int iSwapChain = -1);
		int		CreateSwapchain(MX11SwapChainConfig* pConfig);
		int		CreateViewPort(D3D11_VIEWPORT viewport);

		ResourcePtr GetSwapChainResource(int ID);
		MX11RenderTargetView* GetRenderTargetView(int ID);
		MX11ViewPort* GetViewPort(int ID);

	public:
		MX11PipelineManager*	m_pPipeline;

	protected:
		ID3D11Device*	m_pDevice;
		ID3D11Debug*	m_pDebugger;

		TArray<MX11SwapChain*> m_vSwapChains;

		TArray<IMX11Resource*> m_vResources;

		TArray<MX11RenderTargetView*>	m_vRenderTargetViews;

		TArray<MX11ViewPort*>	m_vViewPorts;
		

		D3D_FEATURE_LEVEL m_FeatureLevel;

		static MX11Renderer*	m_spRenderer;
	};
}
#endif