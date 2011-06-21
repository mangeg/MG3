#include "MG3.h"
#include "Application.h"
#include "ScriptConsole.h"

using namespace MG3;

//------------------------------------------------------------------------|
int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	Application* pApp = Application::GetApplication();
	if(!pApp)
	{
		return -1;
	}

	if(!pApp->SetupComponents())
	{
		return -1;
	}

	if(!pApp->Initialize())
	{
		pApp->UnloadComponents();
		return -1;
	}

	ScriptConsole::ShowConsole(hInstance);

	MSG msg;
	bool loop = true;
	while(loop)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if(msg.message == WM_QUIT)
			{
				loop = false;
				break;
			}
		}

		pApp->Update();
	}

	pApp->Exit();
	pApp->UnloadComponents();

	return 1;
}

//------------------------------------------------------------------------|
LRESULT CALLBACK WindowProc(HWND hWnd, 
	UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE: 
		{
			return( 0 );
		} break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}