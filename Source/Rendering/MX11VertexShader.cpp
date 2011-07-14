//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11VertexShader.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11VertexShader::MX11VertexShader(ID3D11VertexShader* pVertexShader)
{
	m_pVertexShader = pVertexShader;
}
//------------------------------------------------------------------------|
MX11VertexShader::~MX11VertexShader()
{
	SAFE_RELEASE(m_pVertexShader);
}