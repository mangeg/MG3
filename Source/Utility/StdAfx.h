//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
#pragma warning(push)
#pragma warning( disable : 4244 )
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <set>
#include <map>
#pragma warning(pop)
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <time.h>
#include <tchar.h>
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
// DX
#include <DXGI.h>
#include <D3D11.h>
#include <D3D11Shader.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3DCompiler.h>
#include <DxErr.h>
#include <xnamath.h>
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
// WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <shlobj.h>
#include <initguid.h>
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "DxErr.lib")
#ifdef _DEBUG
#pragma comment(lib, "D3DX11D.lib")
#else
#pragma comment(lib, "D3DX11.lib")
#endif
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "dxguid.lib")
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
#if defined _DEBUG 
#define MG_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__) 
#else
#define MG_NEW new
#endif
#define SAFE_DELETE( x ) {if(x){delete (x);(x)=NULL;}}
#define SAFE_DELETE_ARRAY( x ) {if(x){delete[] (x);(x)=NULL;}}
#define SAFE_RELEASE( x ) {if(x){x->Release(); x = NULL;}}
//------------------------------------------------------------------------|

#include "FileSystem.h"
#include "MGUtils.h"
#include "Log.h"