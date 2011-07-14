//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11RasterizerStateConfig : public D3D11_RASTERIZER_DESC
	{
	public:
		MX11RasterizerStateConfig();
		virtual ~MX11RasterizerStateConfig();

		void SetDefaults();

	protected:
		
		friend MX11Renderer;
	};
}