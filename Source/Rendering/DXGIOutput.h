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
	
	protected:
		IDXGIOutput*	m_pOutput;

		friend MX11Renderer;
	};
}