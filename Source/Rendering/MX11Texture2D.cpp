//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Texture2D.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11Texture2D::MX11Texture2D(ID3D11Texture2D* pTexture)
{
	m_pTexture = pTexture;

	ZeroMemory(&m_DesiredDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&m_ActualDesc, sizeof(D3D11_TEXTURE2D_DESC));
}
//------------------------------------------------------------------------|
MX11Texture2D::~MX11Texture2D()
{
	SAFE_RELEASE(m_pTexture);
}
//------------------------------------------------------------------------|
D3D11_TEXTURE2D_DESC MX11Texture2D::GetActualDescription()
{
	ZeroMemory(&m_ActualDesc, sizeof(D3D11_TEXTURE2D_DESC));

	if(m_pTexture)
		m_pTexture->GetDesc(&m_ActualDesc);

	return m_ActualDesc;
}
//------------------------------------------------------------------------|
D3D11_TEXTURE2D_DESC MX11Texture2D::GetDesiredDescription()
{
	return m_DesiredDesc;
}
//------------------------------------------------------------------------|
void MX11Texture2D::SetDesiredDescription( D3D11_TEXTURE2D_DESC description )
{
	m_DesiredDesc = description;
}
//------------------------------------------------------------------------|
D3D11_RESOURCE_DIMENSION MX11Texture2D::GetType()
{
	D3D11_RESOURCE_DIMENSION dim;
	ZeroMemory(&dim, sizeof(D3D11_RESOURCE_DIMENSION));

	if(m_pTexture)
		m_pTexture->GetType(&dim);

	return dim;
}
//------------------------------------------------------------------------|
ID3D11Resource* MX11Texture2D::GetResource()
{
	return m_pTexture;
}
//------------------------------------------------------------------------|
UINT MX11Texture2D::GetEvictionPriority()
{
	UINT prio = 0;

	if(m_pTexture)
		prio = m_pTexture->GetEvictionPriority();

	return prio;
}
//------------------------------------------------------------------------|
void MX11Texture2D::SetEvictionPriority(UINT EvictionPriority)
{
	if(m_pTexture)
		m_pTexture->SetEvictionPriority(EvictionPriority);
}