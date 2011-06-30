//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11RenderTargetView.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11RenderTargetView::MX11RenderTargetView(ID3D11RenderTargetView* pRTView)
{
	m_pRTView = pRTView;
}
//------------------------------------------------------------------------|
MX11RenderTargetView::~MX11RenderTargetView()
{
	SAFE_RELEASE(m_pRTView);
}