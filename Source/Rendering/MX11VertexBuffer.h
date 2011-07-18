//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Buffer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11VertexBuffer : public MX11Buffer
	{
	public:
		MX11VertexBuffer(ID3D11Buffer* pBuffer);
		virtual ~MX11VertexBuffer();

		void SetVertexCount(int count);
		void SetVertexSize(int size);

	protected:
		int	m_iVertexSize;
		int	m_iVertexCount;

		friend MX11Renderer;
	};
}