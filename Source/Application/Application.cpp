
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

	m_pEventManager = new EventManager();
}

//------------------------------------------------------------------------|
Application::~Application()
{	
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