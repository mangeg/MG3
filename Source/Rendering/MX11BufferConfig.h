//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include <D3D11.h>
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Renderer;

	class MX11BufferConfig
	{
	public:
		MX11BufferConfig();
		virtual ~MX11BufferConfig();

		void SetDefaults();
		
		void SetDefaultVertexBuffer(UINT size, bool dynamic);

		void SetBytesWidth(UINT width);
		void SetUsage(D3D11_USAGE usage);
		void SetBindFlags(UINT flags);
		void SetCPUAccessFlags(UINT flags);
		void SetMiscFlags(UINT flags);
		void SetScructuredByteStride(UINT stride);


	protected:
		D3D11_BUFFER_DESC	m_Desc;

		friend MX11Renderer;
	};
}