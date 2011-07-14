//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11Shader
	{
	public:
		MX11Shader();
		virtual ~MX11Shader();

		virtual ShaderType GetType() = 0;

	public:
		ID3DBlob*	m_pCompiledShader;

	protected:
		
	};
}