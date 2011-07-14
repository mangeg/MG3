//------------------------------------------------------------------------|
#pragma once

//------------------------------------------------------------------------|
#include "Application.h"
#include "W32Window.h"
#include "EventManager.h"
#include "IEventHandler.h"
#include "MX11Renderer.h"

namespace MG3
{
	class MX11RenderEffect;

	class BasicApplication : public Application
	{
	public:
		BasicApplication();
	
		virtual bool SetupComponents();
		virtual bool Initialize();
		virtual void Update();
		virtual void Exit();
		virtual void UnloadComponents();

		virtual bool HandleEvent(IEventData const& pEvent);
		virtual std::wstring GetName();

		EventManager* m_pEventManager;

	protected:

		W32Window* m_pWindow;

		MX11Renderer* m_pRenderer;

		ResourcePtr	m_RenderTarget;

		int			m_iSwapChain;

		ID3D11Buffer*		m_pVB;

		MX11RenderEffect*	m_pEffect;
	};
}