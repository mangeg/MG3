//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11RenderParameter.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11VectorParameter : public MX11RenderParameter
	{
	public:
		MX11VectorParameter();
		virtual ~MX11VectorParameter();

		virtual void SetParameterData(void* pData);
		virtual const ParameterType GetParameterType() const;
		virtual void UpdateValue(MX11RenderParameter* pParameter);

		XMFLOAT4 GetVector();
		void SetVector(XMFLOAT4 vector);

	protected:
		XMFLOAT4	m_Vector;
	};
}