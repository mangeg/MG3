//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
#include "MX11ResourceProxy.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11SwapChain
	{
	public:
		MX11SwapChain(IDXGISwapChain* pSwapChain, ResourcePtr resource);
		virtual ~MX11SwapChain();

		IDXGISwapChain* Get();

	protected:
		IDXGISwapChain*	m_pSwapChain;
		ResourcePtr		m_Resource;

		friend MX11Renderer;
	};
}