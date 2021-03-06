//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11SwapChain.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11SwapChain::MX11SwapChain(IDXGISwapChain* pSwapChain, ResourcePtr resource)
{
	m_pSwapChain = pSwapChain;
	m_Resource = resource;
}
//------------------------------------------------------------------------|
MX11SwapChain::~MX11SwapChain()
{
	m_pSwapChain->SetFullscreenState(FALSE, NULL);
	SAFE_RELEASE(m_pSwapChain);
	m_Resource = ResourcePtr();
}
//------------------------------------------------------------------------|
IDXGISwapChain* MX11SwapChain::Get()
{
	return m_pSwapChain;
}