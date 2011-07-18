//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11RenderParameter.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11ConstantBufferParameter : public MX11RenderParameter
	{
	public:
		MX11ConstantBufferParameter();
		MX11ConstantBufferParameter(MX11ConstantBufferParameter& copy);
		virtual ~MX11ConstantBufferParameter();

		int GetIndex();

		virtual void SetParameterData(void* pData);
		virtual const ParameterType GetParameterType() const;
		virtual void UpdateValue(MX11RenderParameter* pParameter);		
	protected:
		int	m_iCBuffer;
	};
}