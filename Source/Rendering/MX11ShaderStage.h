//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Shader.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Renderer;

	class MX11ShaderStage
	{
	public:
		MX11ShaderStage();
		virtual ~MX11ShaderStage();

		void SetCBuffer(int index, ID3D11Buffer* pBuffer);

		void BindResources(ID3D11DeviceContext* pContext);

		virtual ShaderType GetType() = 0;
		virtual void BindConstantBuffers( ID3D11DeviceContext* pContext, int count ) = 0;

	protected:
		ID3D11Buffer*	ConstantBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

		int iCurrMaxCB, iNextMaxCB;
		bool bBuffersDirty;

		friend MX11Renderer;
	};
}