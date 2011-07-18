//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "IParameterManager.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11ParameterManager : public IParamaterManager
	{
	public:
		MX11ParameterManager();
		virtual ~MX11ParameterManager();

		virtual MX11RenderParameter* GetParamRef(const HashedString ParamID) const;
		virtual MX11VectorParameter* GetVectorParamRef(const HashedString ParamID) const;
		virtual MX11ConstantBufferParameter* GetCBufferParamRef(const HashedString ParamID) const;

		virtual MX11RenderParameter* GetParamRef(const std::wstring& name) const;

		virtual XMFLOAT4 GetVectorParameter(MX11RenderParameter* pParameter);
		virtual int GetCBufferParameter(MX11RenderParameter* pParameter);

		virtual void SetCBufferParameter(MX11RenderParameter* pParameter, ResourcePtr resource);

		static std::map<unsigned long, MX11RenderParameter*>	m_Parameters;
	protected:
		IParamaterManager*	m_pParent;		
	};
}