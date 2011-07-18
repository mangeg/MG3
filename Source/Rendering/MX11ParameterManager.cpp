//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11ParameterManager.h"
#include "MX11VectorParameter.h"
#include "MX11ConstantBufferParameter.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
std::map<unsigned long, MX11RenderParameter*> MX11ParameterManager::m_Parameters;
//------------------------------------------------------------------------|
MX11ParameterManager::MX11ParameterManager()
{
	m_pParent = NULL;
}
//------------------------------------------------------------------------|
MX11ParameterManager::~MX11ParameterManager()
{
	std::map<unsigned long, MX11RenderParameter*>::iterator it = m_Parameters.begin();
	for(; it != m_Parameters.end(); it++)
		delete (*it).second;
}
//------------------------------------------------------------------------|
MX11RenderParameter* MX11ParameterManager::GetParamRef(const HashedString ParamID) const
{
	MX11RenderParameter* pParam = m_Parameters[ParamID.GetIdent()];

	if(!pParam && m_pParent)
		pParam = m_pParent->GetParamRef(ParamID);

	return pParam;
}
//------------------------------------------------------------------------|
MX11VectorParameter* MX11ParameterManager::GetVectorParamRef(const HashedString ParamID) const
{
	MX11RenderParameter* pParam = GetParamRef(ParamID);

	if(!pParam)
	{
		pParam = MG_NEW MX11VectorParameter();
		pParam->SetIdent(ParamID);
		m_Parameters[ParamID.GetIdent()] = pParam;
	}

	return static_cast<MX11VectorParameter*>(pParam);
}
//------------------------------------------------------------------------|
MX11ConstantBufferParameter* MX11ParameterManager::GetCBufferParamRef(const HashedString ParamID) const
{
	MX11RenderParameter* pParam = GetParamRef(ParamID);

	if(!pParam)
	{
		pParam = MG_NEW MX11ConstantBufferParameter();
		pParam->SetIdent(ParamID);
		m_Parameters[ParamID.GetIdent()] = pParam;
	}

	return static_cast<MX11ConstantBufferParameter*>(pParam);
}
//------------------------------------------------------------------------|
MX11RenderParameter* MX11ParameterManager::GetParamRef(const std::wstring& name) const
{
	return GetParamRef(HashedString(name.c_str()));
}
//------------------------------------------------------------------------|
XMFLOAT4 MX11ParameterManager::GetVectorParameter(MX11RenderParameter* pParmater)
{
	XMFLOAT4 result = XMFLOAT4(0, 0, 0, 0);

	if(pParmater->GetParameterType() == VECTOR)
		result = static_cast<MX11VectorParameter*>(pParmater)->GetVector();

	return result;
}
//------------------------------------------------------------------------|
int MX11ParameterManager::GetCBufferParameter(MX11RenderParameter* pParameter)
{
	int result = -1;

	if(pParameter->GetParameterType() == CBUFFER)
		result = static_cast<MX11ConstantBufferParameter*>(pParameter)->GetIndex();

	return result;
}
//------------------------------------------------------------------------|
void MX11ParameterManager::SetCBufferParameter(MX11RenderParameter* pParameter, ResourcePtr resource)
{
	if(pParameter->GetParameterType() == CBUFFER)
		pParameter->SetParameterData(reinterpret_cast<void*>(&resource->m_iResource));
	else
		Log::Get() << L"Constant buffer parameter name collision." << Flush;
}