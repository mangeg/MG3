//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
#ifndef MX11RenderTargetViewConfig_H
#define MX11RenderTargetViewConfig_H
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11RenderTargetViewConfig
	{
	public:
		MX11RenderTargetViewConfig();
		virtual ~MX11RenderTargetViewConfig();

		void SetDefaults();

		void SetFormat( DXGI_FORMAT state );
		void SetViewDimensions( D3D11_RTV_DIMENSION state );        

		void SetBuffer( D3D11_BUFFER_RTV state );        
		void SetTexture1D( D3D11_TEX1D_RTV state );
		void SetTexture1DArray( D3D11_TEX1D_ARRAY_RTV state );
		void SetTexture2D( D3D11_TEX2D_RTV state );
		void SetTexture2DArray( D3D11_TEX2D_ARRAY_RTV state );
		void SetTexture2DMS( D3D11_TEX2DMS_RTV state );
		void SetTexture2DMSArray( D3D11_TEX2DMS_ARRAY_RTV state );
		void SetTexture3D( D3D11_TEX3D_RTV state );        

		D3D11_RENDER_TARGET_VIEW_DESC& GetRTVDesc();

	protected:
		D3D11_RENDER_TARGET_VIEW_DESC 		m_Desc;

		friend MX11Renderer;
	};
}
#endif