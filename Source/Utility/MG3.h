#pragma once

#include <string>
#include <list>

#include <stdio.h>

#include <windows.h>

#define SAFE_DELETE( x ) {if(x){delete (x);(x)=NULL;}}
#define SAFE_DELETE_ARRAY( x ) {if(x){delete[] (x);(x)=NULL;}}