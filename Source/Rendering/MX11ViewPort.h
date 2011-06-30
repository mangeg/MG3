//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11ViewPort
	{
	public:
		MX11ViewPort(D3D11_VIEWPORT viewport);
		virtual ~MX11ViewPort();

	protected:
		D3D11_VIEWPORT	m_Desc;

		friend MX11PipelineManager;
	};
}