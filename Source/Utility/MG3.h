#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <string>
#include <list>

#include <stdio.h>

#include <windows.h>

#include <D3D11.h>

#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3D11.lib")

#define SAFE_DELETE( x ) {if(x){delete (x);(x)=NULL;}}
#define SAFE_DELETE_ARRAY( x ) {if(x){delete[] (x);(x)=NULL;}}
#define SAFE_RELEASE( x ) {if(x){x->Release(); x = NULL;}}