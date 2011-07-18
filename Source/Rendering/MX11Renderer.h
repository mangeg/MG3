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
	class MX11VertexBuffer;
	class MX11SwapChain;
	class MX11Texture2D;

	// Configs
	class MX11SwapChainConfig;
	class MX11Texture2DConfig;
	class MX11BufferConfig;	

	class MX11RasterizerStateConfig;

	// Views
	class MX11RenderTargetView;
	class MX11DeptStencilView;
	
	class MX11Shader;

	// States
	class MX11RasterizerState;
	class MX11InputLayout;

	class MX11PipelineManager;
	class MX11ParameterManager;

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

	enum ShaderType
	{
		SHADER_VERTEX = 0,
		SHADER_HULL = 1,
		SHADER_DOMAIN = 2,
		SHADER_GEOMETRY = 3,
		SHADER_PIXEL = 4,
		SHADER_COMPUTE = 5,
		NUM_SHADER_TYPES,
	};

	class MX11Renderer
	{
	public:
		MX11Renderer();
		virtual ~MX11Renderer();

		static MX11Renderer*	Get();

		virtual bool	Initialize();
		virtual void	Shutdown();
		
		int	CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc);
		int CreateDeptStenchilView(int ResourceID, D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc);

		virtual void	Present(int iSwapChain = -1);
		int		CreateSwapchain(MX11SwapChainConfig* pConfig);
		int		CreateViewPort(D3D11_VIEWPORT viewport);

		int LoadShader(ShaderType type, std::wstring const& file, std::wstring const& entry, std::wstring const& profile);

		int CreateInputLayout(TArray<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID);

		ResourcePtr CreateVertexBuffer(MX11BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData);
		ResourcePtr CreateConstantBuffer(MX11BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData, bool bAutoUpdate = true);

		ResourcePtr GetSwapChainResource(int ID);
		ResourcePtr CreateTexture2D(MX11Texture2DConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData);

		MX11RenderTargetView*	GetRenderTargetView(int ID);
		MX11DeptStencilView*	GetDeptStencilView(int ID);
		MX11ViewPort*			GetViewPort(int ID);
		MX11Shader*				GetShader(int ID);
		IMX11Resource*			GetResource(int ID);

		int CreateRasterizerState(MX11RasterizerStateConfig* pConfig);

		boost::shared_ptr<MX11RasterizerState> GetRasterizerState(int ID);
		boost::shared_ptr<MX11InputLayout> GetInputLayout(int ID);

	public:
		MX11PipelineManager*	m_pPipeline;
		MX11ParameterManager*	m_pParamManager;
		ID3D11Device*	m_pDevice;
	protected:
		
		ID3D11Debug*	m_pDebugger;

		TArray<MX11SwapChain*> m_vSwapChains;

		TArray<IMX11Resource*> m_vResources;
		//------------------------------------------------------------------------|
		TArray<MX11RenderTargetView*>	m_vRenderTargetViews;
		TArray<MX11DeptStencilView*>	m_vDeptStencilViews;
		//------------------------------------------------------------------------|
		TArray<MX11Shader*>				m_vShaders;
		//------------------------------------------------------------------------|
		TArray<boost::shared_ptr<MX11RasterizerState>>	m_vRasterizerStates;
		TArray<boost::shared_ptr<MX11InputLayout>>		m_vInputLayouts;

		TArray<MX11ViewPort*>	m_vViewPorts;
		

		D3D_FEATURE_LEVEL m_FeatureLevel;

		static MX11Renderer*	m_spRenderer;
	};
}
#endif