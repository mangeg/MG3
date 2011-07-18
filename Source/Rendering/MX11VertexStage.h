//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11ShaderStage.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11VertexStage : public MX11ShaderStage
	{
	public:
		MX11VertexStage();
		virtual ~MX11VertexStage();

		virtual ShaderType GetType() { return SHADER_VERTEX; }
		virtual void BindConstantBuffers( ID3D11DeviceContext* pContext, int count );

	protected:
		
	};
}