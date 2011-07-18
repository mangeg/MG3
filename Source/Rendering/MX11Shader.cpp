//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11Shader.h"
#include "MX11PipelineManager.h"
#include "IParameterManager.h"
#include "MX11BufferConfig.h"
#include "MX11ConstantBuffer.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11Shader::MX11Shader()
{
}
//------------------------------------------------------------------------|
MX11Shader::~MX11Shader()
{
	SAFE_RELEASE(CompiledShader);
}
//------------------------------------------------------------------------|
void MX11Shader::UpdateParameters(MX11PipelineManager* pPipeline, IParamaterManager* pParamManager)
{
	for(int i = 0; i < ConstantBuffers.Size(); i++)
	{
		ConstantBufferLayout& cbuffer = ConstantBuffers[i];
		if(cbuffer.Description.Type == D3D11_CT_CBUFFER)
		{
			int index = pParamManager->GetCBufferParameter(cbuffer.pParamRef);

			if(index == -1)
			{
				MX11BufferConfig cbufferConfig;
				cbufferConfig.SetDefaultCBuffer(cbuffer.Description.Size, true);

				ResourcePtr resource = MX11Renderer::Get()->CreateConstantBuffer(&cbufferConfig, NULL);
				index = resource->m_iResource;

				pParamManager->SetCBufferParameter(cbuffer.pParamRef, resource);
			}

			if ( (index & 0x00FF0000) == RT_CONSTANTBUFFER ) 
			{
				MX11ConstantBuffer* pBuffer = static_cast<MX11ConstantBuffer*>(MX11Renderer::Get()->GetResource( index & 0x0000FFFF ));
				
				if(pBuffer->GetAutoUpdate())
				{
					D3D11_MAPPED_SUBRESOURCE resource = pPipeline->MapResource(index, 0, D3D11_MAP_WRITE_DISCARD, 0);

					for(int j = 0; j < cbuffer.Variables.Size(); j++)
					{
						ShaderVariableDesc var = cbuffer.Variables[j];
						MX11RenderParameter* pParam = cbuffer.Parameters[j];
						int offset = var.StartOffset;
						UINT size = var.Size;

						if(cbuffer.Types[j].Class == D3D10_SVC_VECTOR)
						{
							XMFLOAT4 vector = pParamManager->GetVectorParameter(pParam);
							XMFLOAT4* pBuff = reinterpret_cast<XMFLOAT4*>((char*)resource.pData + offset);
							*pBuff = vector;
						}
					}

					pPipeline->UnMapResource(index, 0);
				}
			}
		}
	}
}
//------------------------------------------------------------------------|
void MX11Shader::BindParameters(MX11PipelineManager* pPipeline, IParamaterManager* pParamManager)
{
	for(int i = 0; i < ResourceBindings.Size(); i++)
	{
		ShaderInputBindDesc binding = ResourceBindings[i];
		UINT slot = binding.BindPoint;

		switch(ResourceBindings[i].Type)
		{
		case D3D10_SIT_CBUFFER:
		case D3D10_SIT_TBUFFER:
			pPipeline->BindCBufferParameter(GetType(), binding.pParamRef, slot, pParamManager);
			break;
		}
	}
}