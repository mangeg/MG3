//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IMX11Resource.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Buffer : public IMX11Resource
	{
	public:
		MX11Buffer();
		virtual ~MX11Buffer();

		D3D11_BUFFER_DESC			GetActualDescription();
		D3D11_BUFFER_DESC			GetDesiredDescription();
		void						SetDesiredDescription( D3D11_BUFFER_DESC desc );

		UINT						GetByteWidth();
		void						SetByteWidth( UINT width );

		D3D11_USAGE					GetUsage();
		void						SetUsage( D3D11_USAGE usage );

		UINT						GetBindFlags();
		void						SetBindFlags( UINT flags );

		UINT						GetCPUAccessFlags();
		void						SetCPUAccessFlags( UINT flags );

		UINT						GetMiscFlags();
		void						SetMiscFlags( UINT flags );

		UINT						GetStructureByteStride();
		void						SetStructureByteStride( UINT stride );

		void*						Map();
		void						UnMap();

		virtual D3D11_RESOURCE_DIMENSION	GetType();
		virtual ID3D11Resource*				GetResource();

		virtual UINT						GetEvictionPriority();
		virtual void						SetEvictionPriority( UINT EvictionPriority );

	protected:
		ID3D11Buffer*	m_pBuffer;
		D3D11_BUFFER_DESC	m_ActualDesc;
		D3D11_BUFFER_DESC	m_DesiredDesc;

		friend MX11Renderer;
	};
}