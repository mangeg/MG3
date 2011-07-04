//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "Application.h"
#include "IEventManager.h"
#include "EvtKeyboardChar.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	//_crtBreakAlloc = 161;
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Log StandardLog(FileSystem::GetAppDataFolder().c_str(), L"General.log", true);

	Application* pApp = Application::GetApplication();
	if(!pApp)
	{
		return -1;
	}

	pApp->SetInstance(hInstance);

	if(!pApp->SetupComponents())
	{
		Log::Get() << L"SetupComponents failed";
		return -1;
	}

	if(!pApp->Initialize())
	{
		Log::Get() << L"Failed to initialize application";
		pApp->UnloadComponents();
		return -1;
	}	

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

	Log::Get() << L"Application exiting";
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
	case WM_CHAR:
		{
			IEventManager::Get()->Fire(EvtKeyboardChar(hWnd, wParam, lParam));
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}