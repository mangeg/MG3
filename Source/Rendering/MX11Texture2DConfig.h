//------------------------------------------------------------------------|
#ifndef MX11Texture2DConfig_H
#define MX11Texture2DConfig_H
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Texture2DConfig
	{
	public:
		MX11Texture2DConfig();
		virtual ~MX11Texture2DConfig();

		void SetDefaults();
		void SetDepthBuffer( UINT width, UINT height );
		void SetColorBuffer( UINT width, UINT height );

		void SetWidth( UINT state );
		void SetHeight( UINT state );
		void SetMipLevels( UINT state );
		void SetArraySize( UINT state );
		void SetFormat( DXGI_FORMAT state );
		void SetSampleDesc( DXGI_SAMPLE_DESC state );
		void SetUsage( D3D11_USAGE state ); 
		void SetBindFlags( UINT state );
		void SetCPUAccessFlags( UINT state );
		void SetMiscFlags( UINT state );

		D3D11_TEXTURE2D_DESC GetTextureDesc();

	protected:
		D3D11_TEXTURE2D_DESC	m_Desc;

		friend MX11Renderer;
	};
}
#endif