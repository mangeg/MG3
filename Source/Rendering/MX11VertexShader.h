//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Shader.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11PipelineManager;

	class MX11VertexShader : public MX11Shader
	{
	public:
		MX11VertexShader(ID3D11VertexShader* pVertexShader);
		virtual ~MX11VertexShader();

		virtual ShaderType GetType() { return SHADER_VERTEX; }

		ID3D11VertexShader* GetShader() { return m_pVertexShader; }

	protected:
		ID3D11VertexShader*	m_pVertexShader;

		friend MX11PipelineManager;
	};
}