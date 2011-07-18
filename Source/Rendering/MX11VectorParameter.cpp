//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11VectorParameter.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11VectorParameter::MX11VectorParameter()
{
	m_Vector = XMFLOAT4(0, 0, 0, 0);
}
//------------------------------------------------------------------------|
MX11VectorParameter::~MX11VectorParameter()
{
}
//------------------------------------------------------------------------|
void MX11VectorParameter::SetParameterData(void* pData)
{
	m_Vector = *reinterpret_cast<XMFLOAT4*>(pData);
}
//------------------------------------------------------------------------|
const ParameterType MX11VectorParameter::GetParameterType() const
{
	return VECTOR;
}
//------------------------------------------------------------------------|
void MX11VectorParameter::UpdateValue(MX11RenderParameter* pParameter)
{
	if(pParameter)
	{
		if(pParameter->GetParameterType() ==  VECTOR && pParameter->GetIdent().GetIdent() == m_Ident.GetIdent())
		{
			MX11VectorParameter* pVector = static_cast<MX11VectorParameter*>(pParameter);
			m_Vector = pVector->GetVector();
		}
	}
}
//------------------------------------------------------------------------|
XMFLOAT4 MX11VectorParameter::GetVector()
{
	return m_Vector;
}
//------------------------------------------------------------------------|
void MX11VectorParameter::SetVector(XMFLOAT4 vector)
{
	m_Vector = vector;
}