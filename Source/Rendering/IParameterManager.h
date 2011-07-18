//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "HashedString.h"
#include "IMX11Resource.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11RenderParameter;
	class MX11VectorParameter;
	class MX11ConstantBufferParameter;

	class IParamaterManager
	{
	public:
		IParamaterManager() {};
		virtual ~IParamaterManager() {};

		virtual MX11RenderParameter* GetParamRef(const HashedString ParamID) const = 0;
		virtual MX11VectorParameter* GetVectorParamRef(const HashedString ParamID) const = 0;
		virtual MX11ConstantBufferParameter* GetCBufferParamRef(const HashedString ParamID) const = 0;

		virtual MX11RenderParameter* GetParamRef(const std::wstring& name) const = 0;

		virtual XMFLOAT4 GetVectorParameter(MX11RenderParameter* pParmeter) = 0;
		virtual int GetCBufferParameter(MX11RenderParameter* pParameter) = 0;

		virtual void SetCBufferParameter(MX11RenderParameter* pParameter, ResourcePtr resource) = 0;

	protected:
		
	};
}