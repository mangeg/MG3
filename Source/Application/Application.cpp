
#include "StdAfx.h"
#include "Application.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
Application* Application::ms_pAppliction = NULL;

//------------------------------------------------------------------------|
Application::Application()
{
	ms_pAppliction = this;	

	m_pTimer = MG_NEW Timer();
	m_pTimer->Update();
}

//------------------------------------------------------------------------|
Application::~Application()
{		
	SAFE_DELETE(m_pTimer);
}

//------------------------------------------------------------------------|
Application* Application::GetApplication()
{
	return ms_pAppliction;
}

//------------------------------------------------------------------------|
void Application::DoExit()
{
	PostQuitMessage(0);
}