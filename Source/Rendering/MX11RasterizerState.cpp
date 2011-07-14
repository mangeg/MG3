//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11RasterizerState.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11RasterizerState::MX11RasterizerState(ID3D11RasterizerState* pState)
{
	m_pState = pState;
}
//------------------------------------------------------------------------|
MX11RasterizerState::~MX11RasterizerState()
{
	SAFE_RELEASE(m_pState);
}