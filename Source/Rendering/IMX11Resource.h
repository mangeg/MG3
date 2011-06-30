//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class IMX11Resource
	{
	public:
		virtual ~IMX11Resource() {};

		virtual D3D11_RESOURCE_DIMENSION	GetType() = 0;
		virtual ID3D11Resource*				GetResource() = 0;

		virtual UINT	GetEvictionPriority() = 0;
		virtual void	SetEvictionPriority( UINT EvictionPriority ) = 0;
	};
}