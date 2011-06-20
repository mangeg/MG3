#include "Application.h"

using namespace MG3;

Application* Application::ms_pAppliction = NULL;

Application::Application()
{
	ms_pAppliction = this;
}

Application* Application::GetApplication()
{
	return ms_pAppliction;
}