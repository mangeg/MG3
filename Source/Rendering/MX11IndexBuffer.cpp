//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11IndexBuffer.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11IndexBuffer::MX11IndexBuffer(ID3D11Buffer* pBuffer)
{
	m_pBuffer = pBuffer;
}
//------------------------------------------------------------------------|
MX11IndexBuffer::~MX11IndexBuffer()
{
}
//------------------------------------------------------------------------|
void MX11IndexBuffer::SetIndexCount(int count)
{
	m_iIndexCount = count;
}
//------------------------------------------------------------------------|
void MX11IndexBuffer::SetIndexSize(int size)
{
	m_iIndexSize = size;
}