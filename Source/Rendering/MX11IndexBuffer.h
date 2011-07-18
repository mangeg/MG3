//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Buffer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11IndexBuffer : public MX11Buffer
	{
	public:
		MX11IndexBuffer(ID3D11Buffer* pBuffer);
		virtual ~MX11IndexBuffer();

		void SetIndexCount(int count);
		void SetIndexSize(int size);

	protected:
		int	m_iIndexSize;
		int	m_iIndexCount;

		friend MX11Renderer;
	};
}