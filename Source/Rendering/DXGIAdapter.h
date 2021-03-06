//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Renderer.h"
#include "DXGIOutput.h"
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
		TArray<DXGIOutput*> m_vOutputs;

		DXGI_ADAPTER_DESC1 m_Desc;

		friend MX11Renderer;
	};
}