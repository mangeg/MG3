//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11VertexBuffer.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11VertexBuffer::MX11VertexBuffer(ID3D11Buffer* pBuffer)
{
	m_pBuffer = pBuffer;
}
//------------------------------------------------------------------------|
MX11VertexBuffer::~MX11VertexBuffer()
{
}
//------------------------------------------------------------------------|
void MX11VertexBuffer::SetVertexCount(int count)
{
	m_iVertexCount = count;
}
//------------------------------------------------------------------------|
void MX11VertexBuffer::SetVertexSize(int size)
{
	m_iVertexSize = size;
}