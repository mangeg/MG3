//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11PixelShader.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11PixelShader::MX11PixelShader( ID3D11PixelShader* pShader )
{
	m_pPixelShader = pShader;
}
//------------------------------------------------------------------------|
MX11PixelShader::~MX11PixelShader()
{
	SAFE_RELEASE(m_pPixelShader);
}