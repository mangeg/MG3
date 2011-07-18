//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11ConstantBufferParameter.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11ConstantBufferParameter::MX11ConstantBufferParameter()
{
	m_iCBuffer = -1;
}
//------------------------------------------------------------------------|
MX11ConstantBufferParameter::MX11ConstantBufferParameter(MX11ConstantBufferParameter& copy)
{
	m_iCBuffer = copy.m_iCBuffer;
}
//------------------------------------------------------------------------|
MX11ConstantBufferParameter::~MX11ConstantBufferParameter()
{
}
//------------------------------------------------------------------------|
int MX11ConstantBufferParameter::GetIndex()
{
	return m_iCBuffer;
}
//------------------------------------------------------------------------|
void MX11ConstantBufferParameter::SetParameterData(void* pData)
{
	m_iCBuffer = *reinterpret_cast<int*>(pData);
}
//------------------------------------------------------------------------|
const ParameterType MX11ConstantBufferParameter::GetParameterType() const
{
	return CBUFFER;
}
//------------------------------------------------------------------------|
void MX11ConstantBufferParameter::UpdateValue(MX11RenderParameter* pParameter)
{
	if(pParameter)
	{
		if(pParameter->GetParameterType() == CBUFFER && pParameter->GetIdent().GetIdent() == m_Ident.GetIdent())
		{
			MX11ConstantBufferParameter* pCBufferParam = static_cast<MX11ConstantBufferParameter*>(pParameter);
			m_iCBuffer = pCBufferParam->GetIndex();
		}
	}
}