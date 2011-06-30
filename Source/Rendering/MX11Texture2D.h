//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IMX11Resource.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Texture2D : public IMX11Resource
	{
	public:
		MX11Texture2D(ID3D11Texture2D* pTexture);
		virtual ~MX11Texture2D();

		D3D11_TEXTURE2D_DESC		GetActualDescription();
		D3D11_TEXTURE2D_DESC		GetDesiredDescription();
		void						SetDesiredDescription( D3D11_TEXTURE2D_DESC description );

		virtual D3D11_RESOURCE_DIMENSION	GetType();
		virtual ID3D11Resource*				GetResource();

		virtual UINT	GetEvictionPriority();
		virtual void	SetEvictionPriority(UINT EvictionPriority);

	protected:
		ID3D11Texture2D*			m_pTexture;
		D3D11_TEXTURE2D_DESC		m_DesiredDesc;
		D3D11_TEXTURE2D_DESC		m_ActualDesc;

		friend MX11Renderer;
	};
}