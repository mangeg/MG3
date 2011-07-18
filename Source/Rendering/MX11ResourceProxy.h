//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Renderer;
	class MX11RenderTargetViewConfig;
	class MX11DeptStencilViewConfig;
	class MX11Texture2DConfig;
	class MX11BufferConfig;

	class MX11ResourceProxy
	{
	public:
		MX11ResourceProxy();
		MX11ResourceProxy(int ResourceID, MX11BufferConfig* pConfig, MX11Renderer* pRenderer,
			MX11RenderTargetViewConfig* pRTVConfig = NULL,
			MX11DeptStencilViewConfig* pDSVConfig = NULL);
		MX11ResourceProxy(int ResourceID, MX11Texture2DConfig* pConfig, MX11Renderer* pRenderer,
			MX11RenderTargetViewConfig* pRTVConfig = NULL,
			MX11DeptStencilViewConfig* pDSVConfig = NULL);
		virtual ~MX11ResourceProxy();

	public:
		int	m_iResource;
		int	m_iRTVResource;
		int m_iDSVResource;

		MX11BufferConfig*		m_pBufferConfig;
		MX11Texture2DConfig*	m_pTexture2DConfig;
		
		MX11RenderTargetViewConfig*	m_pRTVConfig;
		MX11DeptStencilViewConfig* m_pDSVConfig;

		friend MX11Renderer;

	protected:		
		void _Initialize(UINT BindFlags, int ResourceID, MX11Renderer* pRenderer,
			MX11RenderTargetViewConfig* pRTVConfig,
			MX11DeptStencilViewConfig* pDSVConfig);
	};

	typedef boost::shared_ptr<MX11ResourceProxy> ResourcePtr;
}