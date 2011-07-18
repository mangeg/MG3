//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11ConstantBuffer.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11ConstantBuffer::MX11ConstantBuffer(ID3D11Buffer* pBuffer)
{
	m_pBuffer = pBuffer;
	m_bAutoUpdate = true;
}
//------------------------------------------------------------------------|
MX11ConstantBuffer::~MX11ConstantBuffer()
{
}
//------------------------------------------------------------------------|
void MX11ConstantBuffer::SetAutoUpdate(bool update)
{
	m_bAutoUpdate = update;
}
//------------------------------------------------------------------------|
bool MX11ConstantBuffer::GetAutoUpdate()
{
	return m_bAutoUpdate;
}