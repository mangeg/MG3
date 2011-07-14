//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Shader.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11PipelineManager;

	class MX11PixelShader : public MX11Shader
	{
	public:
		MX11PixelShader( ID3D11PixelShader* pPixelShader );
		virtual ~MX11PixelShader();

		virtual ShaderType GetType() { return SHADER_PIXEL; }
		ID3D11PixelShader* GetShader() { return m_pPixelShader; }

	protected:
		ID3D11PixelShader*	m_pPixelShader;

		friend MX11PipelineManager;
	};
}