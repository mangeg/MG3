//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11DeptStencilView.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11DeptStencilView::MX11DeptStencilView( ID3D11DepthStencilView* pView )
{
	m_pView = pView;
}
//------------------------------------------------------------------------|
MX11DeptStencilView::~MX11DeptStencilView()
{
	SAFE_RELEASE(m_pView);
}