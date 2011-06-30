//------------------------------------------------------------------------|
#pragma once

//------------------------------------------------------------------------|
#include "Application.h"
#include "W32Window.h"
#include "IEventHandler.h"
#include "IEvent.h"
#include "MX11Renderer.h"

using namespace MG3;

class BasicApplication : public Application
{
public:
	BasicApplication();
	
	virtual bool SetupComponents();
	virtual bool Initialize();
	virtual void Update();
	virtual void Exit();
	virtual void UnloadComponents();

	virtual bool HandleEvent(IEvent* pEvent);
	virtual std::wstring GetName();

protected:

	W32Window* m_pWindow;

	MX11Renderer* m_pRenderer;

	ResourcePtr	m_RenderTarget;

	int			m_iSwapChain;
};