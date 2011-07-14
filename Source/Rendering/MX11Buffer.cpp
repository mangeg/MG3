//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Buffer.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11Buffer::MX11Buffer()
{
	m_pBuffer = NULL;

	ZeroMemory(&m_ActualDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&m_DesiredDesc, sizeof(D3D11_BUFFER_DESC));
}
//------------------------------------------------------------------------|
MX11Buffer::~MX11Buffer()
{
	SAFE_RELEASE( m_pBuffer );
}
//------------------------------------------------------------------------|
D3D11_BUFFER_DESC MX11Buffer::GetActualDescription()
{
	ZeroMemory(&m_ActualDesc, sizeof(D3D11_BUFFER_DESC));

	if(m_pBuffer)
		m_pBuffer->GetDesc(&m_ActualDesc);

	return m_ActualDesc;
}
//------------------------------------------------------------------------|
D3D11_BUFFER_DESC MX11Buffer::GetDesiredDescription()
{
	return m_DesiredDesc;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetDesiredDescription( D3D11_BUFFER_DESC desc )
{
	m_DesiredDesc = desc;
}
//------------------------------------------------------------------------|
UINT MX11Buffer::GetByteWidth()
{
	D3D11_BUFFER_DESC desc = GetActualDescription();

	return desc.ByteWidth;
}
//------------------------------------------------------------------------|
D3D11_USAGE MX11Buffer::GetUsage()
{
	D3D11_BUFFER_DESC desc = GetActualDescription();

	return desc.Usage;
}
//------------------------------------------------------------------------|
UINT MX11Buffer::GetBindFlags()
{
	D3D11_BUFFER_DESC desc = GetActualDescription();

	return desc.BindFlags;
}
//------------------------------------------------------------------------|
UINT MX11Buffer::GetCPUAccessFlags()
{
	D3D11_BUFFER_DESC desc = GetActualDescription();

	return desc.CPUAccessFlags;
}
//------------------------------------------------------------------------|
UINT MX11Buffer::GetMiscFlags()
{
	D3D11_BUFFER_DESC desc = GetActualDescription();

	return desc.MiscFlags;
}
//------------------------------------------------------------------------|
UINT MX11Buffer::GetStructureByteStride()
{
	D3D11_BUFFER_DESC desc = GetActualDescription();

	return desc.StructureByteStride;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetByteWidth( UINT width )
{
	m_DesiredDesc.ByteWidth = width;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetUsage( D3D11_USAGE usage )
{
	m_DesiredDesc.Usage = usage;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetBindFlags( UINT flags )
{
	m_DesiredDesc.BindFlags = flags;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetCPUAccessFlags( UINT flags )
{
	m_DesiredDesc.CPUAccessFlags = flags;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetMiscFlags( UINT flags )
{
	m_DesiredDesc.MiscFlags = flags;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetStructureByteStride( UINT stride )
{
	m_DesiredDesc.StructureByteStride = stride;
}
//------------------------------------------------------------------------|
void* MX11Buffer::Map()
{
	return 0;
}
//------------------------------------------------------------------------|
void MX11Buffer::UnMap()
{
}


// Virtual functions
//------------------------------------------------------------------------|
D3D11_RESOURCE_DIMENSION MX11Buffer::GetType()
{
	D3D11_RESOURCE_DIMENSION dim;
	ZeroMemory( &dim, sizeof( D3D11_RESOURCE_DIMENSION ) );	

	if ( m_pBuffer )
		m_pBuffer->GetType( &dim );

	return dim;
}
//------------------------------------------------------------------------|
ID3D11Resource*	MX11Buffer::GetResource()
{
	return m_pBuffer;
}
//------------------------------------------------------------------------|
UINT MX11Buffer::GetEvictionPriority()
{
	UINT priority = 0;

	if ( m_pBuffer )
		priority = m_pBuffer->GetEvictionPriority();

	return priority;
}
//------------------------------------------------------------------------|
void MX11Buffer::SetEvictionPriority( UINT EvictionPriority )
{
	if ( m_pBuffer )
		m_pBuffer->SetEvictionPriority( EvictionPriority );
}