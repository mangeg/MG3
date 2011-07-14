//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include <D3DX11.h>
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11PipelineManager;

	class MX11InputLayout
	{
	public:
		MX11InputLayout(ID3D11InputLayout* pLayout);
		virtual ~MX11InputLayout();

	protected:
		ID3D11InputLayout*	m_pLayout;

		friend MX11PipelineManager;
	};
}