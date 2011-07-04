//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class DXGIOutput
	{
	public:
		DXGIOutput(IDXGIOutput* pOutput);
		virtual ~DXGIOutput();

		TCHAR* GetDeviceName();
		DXGI_MODE_ROTATION GetRotation();
		RECT GetRect();
		DXGI_OUTPUT_DESC GetDesc();

	protected:
		IDXGIOutput*	m_pOutput;
		DXGI_OUTPUT_DESC	m_Desc;

		friend MX11Renderer;
	};
}