//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Shader.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11Shader::MX11Shader()
{
}
//------------------------------------------------------------------------|
MX11Shader::~MX11Shader()
{
	SAFE_RELEASE(m_pCompiledShader);
}