//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11InputLayout.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11InputLayout::MX11InputLayout(ID3D11InputLayout* pLayout)
{
	m_pLayout = pLayout;
}
//------------------------------------------------------------------------|
MX11InputLayout::~MX11InputLayout()
{
	SAFE_RELEASE(m_pLayout);
}