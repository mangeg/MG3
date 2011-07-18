//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Buffer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11ConstantBuffer : public MX11Buffer
	{
	public:
		MX11ConstantBuffer(ID3D11Buffer* pBuffer);
		virtual ~MX11ConstantBuffer();

		void SetAutoUpdate(bool update);
		bool GetAutoUpdate();

	protected:
		bool	m_bAutoUpdate;

		friend MX11Renderer;
	};
}