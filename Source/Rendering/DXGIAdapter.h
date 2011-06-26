//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MG3.h"
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class DXGIAdapter
	{
	public:
		DXGIAdapter(IDXGIAdapter1* pAdapter);
		virtual ~DXGIAdapter();

		std::wstring GetName();

	protected:
		IDXGIAdapter1* m_pAdapter;

		DXGI_ADAPTER_DESC1 m_Desc;

		friend MX11Renderer;
	};
}