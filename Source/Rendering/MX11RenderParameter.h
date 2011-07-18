//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "HashedString.h"
//------------------------------------------------------------------------|
namespace MG3
{
	enum ParameterType
	{
		VECTOR,
		MATRIX,
		CBUFFER,
	};

	class MX11RenderParameter
	{
	public:
		MX11RenderParameter();
		MX11RenderParameter(MX11RenderParameter& copy);
		virtual ~MX11RenderParameter();

		void InitializeData(void* pData);

		void SetIdent(const HashedString& ident);
		HashedString& GetIdent();

		virtual void SetParameterData(void* pData) = 0;
		virtual const ParameterType GetParameterType() const = 0;
		virtual void UpdateValue(MX11RenderParameter* pParameter) = 0;

	protected:
		HashedString	m_Ident;
	};
}