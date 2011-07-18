//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11BufferConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11BufferConfig::MX11BufferConfig()
{
	SetDefaults();
}
//------------------------------------------------------------------------|
MX11BufferConfig::~MX11BufferConfig()
{
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetDefaults()
{
	ZeroMemory(&m_Desc, sizeof(D3D11_BUFFER_DESC));

	m_Desc.ByteWidth = 1;
	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_Desc.MiscFlags = 0;
	m_Desc.StructureByteStride = 0;
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetDefaultCBuffer(UINT size, bool dynamic)
{
	m_Desc.ByteWidth = size;
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_Desc.MiscFlags = 0;
	m_Desc.StructureByteStride = 0;

	if(dynamic)
	{
		m_Desc.Usage = D3D11_USAGE_DYNAMIC;
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		m_Desc.CPUAccessFlags = 0;
	}
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetDefaultVertexBuffer(UINT size, bool dynamic)
{
	m_Desc.ByteWidth = size;
	m_Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_Desc.MiscFlags = 0;
	m_Desc.StructureByteStride = 0;

	if(dynamic)
	{
		m_Desc.Usage = D3D11_USAGE_DYNAMIC;
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		m_Desc.CPUAccessFlags = 0;
	}
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetDefaultIndexBuffer(UINT size, bool dynamic)
{
	m_Desc.ByteWidth = size;
	m_Desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_Desc.MiscFlags = 0;
	m_Desc.StructureByteStride = 0;

	if(dynamic)
	{
		m_Desc.Usage = D3D11_USAGE_DYNAMIC;
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_Desc.Usage = D3D11_USAGE_IMMUTABLE;
		m_Desc.CPUAccessFlags = 0;
	}
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetBytesWidth(UINT width)
{
	m_Desc.ByteWidth = width;
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetUsage(D3D11_USAGE usage)
{
	m_Desc.Usage = usage;
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetBindFlags(UINT flags)
{
	m_Desc.BindFlags = flags;
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetCPUAccessFlags(UINT flags)
{
	m_Desc.CPUAccessFlags = flags;
}
//------------------------------------------------------------------------|
void MX11BufferConfig::SetMiscFlags(UINT flags)
{
	m_Desc.MiscFlags = flags;
}
//------------------------------------------------------------------------|'
void MX11BufferConfig::SetScructuredByteStride(UINT stride)
{
	m_Desc.StructureByteStride = stride;
}
//------------------------------------------------------------------------|
D3D11_BUFFER_DESC MX11BufferConfig::GetBufferDesc()
{
	return m_Desc;
}