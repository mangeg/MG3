//------------------------------------------------------------------------|
#pragma once

//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "IEventHandler.h"
#include "Timer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class Application : public IEventHandler
	{
	public:
		Application();
		~Application();

		static Application* GetApplication();

		virtual bool SetupComponents() = 0;
		virtual bool Initialize() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;
		virtual void UnloadComponents() = 0;

		void DoExit();
		HINSTANCE GetInstance(){return m_hInstance;}

		void SetInstance(HINSTANCE hInstance) {m_hInstance = hInstance;}		

	protected:
		static Application* ms_pAppliction;

		HINSTANCE m_hInstance;

		Timer*	m_pTimer;
	};
}
