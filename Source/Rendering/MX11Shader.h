//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
#include "MX11Renderer.h"
#include "StringTools.h"
//------------------------------------------------------------------------|
namespace MG3
{
	class MX11RenderParameter;
	class MX11PipelineManager;
	class IParamaterManager;

	struct SignatureParameterDesc
	{
		SignatureParameterDesc( D3D11_SIGNATURE_PARAMETER_DESC desc )
		{
			SemanticName = std::wstring( StringTools::ToUnicode( std::string( desc.SemanticName ) ) );
			SemanticIndex = desc.SemanticIndex;
			Register = desc.Register;
			SystemValueType = desc.SystemValueType;
			ComponentType = desc.ComponentType;
			Mask = desc.Mask;
			ReadWriteMask = desc.ReadWriteMask;
		};

		SignatureParameterDesc( )
		{
			SemanticName = std::wstring( L"" );
			SemanticIndex = 0;
			Register = 0;
			SystemValueType = D3D10_NAME_UNDEFINED;
			ComponentType = D3D10_REGISTER_COMPONENT_UNKNOWN;
			Mask = 0;
			ReadWriteMask = 0;
		};

		std::wstring SemanticName;
		UINT SemanticIndex;
		UINT Register;
		D3D10_NAME SystemValueType;
		D3D10_REGISTER_COMPONENT_TYPE ComponentType;
		BYTE Mask;
		BYTE ReadWriteMask;
	};

	struct ShaderBufferDesc
	{
		ShaderBufferDesc( D3D11_SHADER_BUFFER_DESC desc )
		{
			Name = std::wstring( StringTools::ToUnicode( std::string( desc.Name ) ) );
			Type = desc.Type;
			Variables = desc.Variables;
			Size = desc.Size;	
			uFlags = desc.uFlags;
		};

		ShaderBufferDesc()
		{
			Name = std::wstring( L"" );
			Type = D3D11_CT_CBUFFER;
			Variables = 0;
			Size = 0;	
			uFlags = 0;
		};

		std::wstring Name;
		D3D11_CBUFFER_TYPE Type;
		UINT Variables;
		UINT Size;
		UINT uFlags;
	};

	struct ShaderVariableDesc
	{
		ShaderVariableDesc( D3D11_SHADER_VARIABLE_DESC desc )
		{
			Name = std::wstring( StringTools::ToUnicode( std::string( desc.Name ) ) );
			StartOffset = desc.StartOffset;
			Size = desc.Size;
			uFlags = desc.uFlags;
			DefaultValue = desc.DefaultValue;
			StartTexture = desc.StartTexture;
			TextureSize = desc.TextureSize;
			StartSampler = desc.StartSampler;
			SamplerSize = desc.SamplerSize;
		};

		ShaderVariableDesc( )
		{
			Name = std::wstring( L"" );
			StartOffset = 0;
			Size = 0;
			uFlags = 0;
			DefaultValue = 0;
			StartTexture = -1;
			TextureSize = 0;
			StartSampler = -1;
			SamplerSize = 0;
		};

		std::wstring Name;           // Name of the variable
		UINT StartOffset;    // Offset in constant buffer's backing store
		UINT Size;           // Size of variable (in bytes)
		UINT uFlags;         // Variable flags
		LPVOID DefaultValue;   // Raw pointer to default value
		UINT StartTexture;   // First texture index (or -1 if no textures used)
		UINT TextureSize;    // Number of texture slots possibly used.
		UINT StartSampler;   // First sampler index (or -1 if no textures used)
		UINT SamplerSize;    // Number of sampler slots possibly used.
	};

	struct ShaderTypeDesc
	{
		ShaderTypeDesc( D3D11_SHADER_TYPE_DESC desc )
		{
			Class = desc.Class;
			Type = desc.Type;  
			Rows = desc.Rows;         
			Columns = desc.Columns;      
			Elements = desc.Elements;     
			Members = desc.Members;      
			Offset = desc.Offset;       
			if ( desc.Name )
				Name = std::wstring( StringTools::ToUnicode( std::string( desc.Name ) ) );  
			else
				Name = std::wstring( L"" );
		};
		ShaderTypeDesc()
		{
			Class = D3D10_SVC_SCALAR;
			Type = D3D10_SVT_VOID;
			Rows = 0;         
			Columns = 0;      
			Elements = 0;     
			Members = 0;      
			Offset = 0;       
			Name = std::wstring( L"" );  
		};

		D3D10_SHADER_VARIABLE_CLASS Class;		// Variable class (e.g. object, matrix, etc.)
		D3D10_SHADER_VARIABLE_TYPE  Type;		// Variable type (e.g. float, sampler, etc.)
		UINT Rows;								// Number of rows (for matrices, 1 for other numeric, 0 if not applicable)
		UINT Columns;							// Number of columns (for vectors & matrices, 1 for other numeric, 0 if not applicable)
		UINT Elements;							// Number of elements (0 if not an array)
		UINT Members;							// Number of members (0 if not a structure)
		UINT Offset;							// Offset from the start of structure (0 if not a structure member)
		std::wstring Name;						// Name of type, can be NULL
	};

	struct ShaderInputBindDesc
	{
		ShaderInputBindDesc( D3D11_SHADER_INPUT_BIND_DESC desc )
		{
			Name = std::wstring( StringTools::ToUnicode( std::string( desc.Name ) ) );
			Type = desc.Type;
			BindPoint = desc.BindPoint;
			BindCount = desc.BindCount;
			uFlags = desc.uFlags;
			ReturnType = desc.ReturnType;
			Dimension = desc.Dimension;
			NumSamples = desc.NumSamples;
			pParamRef = 0;
		};

		ShaderInputBindDesc()
		{
			Name = std::wstring( L"" );
			Type = D3D10_SIT_CBUFFER;
			BindPoint = 0;
			BindCount = 0;
			uFlags = 0;
			ReturnType = D3D11_RETURN_TYPE_UNORM;
			Dimension = D3D10_SRV_DIMENSION_UNKNOWN;
			NumSamples = 0;
			pParamRef = 0;
		};

		std::wstring Name;
		D3D10_SHADER_INPUT_TYPE Type;
		UINT BindPoint;
		UINT BindCount;
		UINT uFlags;
		D3D11_RESOURCE_RETURN_TYPE ReturnType;
		D3D10_SRV_DIMENSION Dimension;
		UINT NumSamples;
		MX11RenderParameter* pParamRef;
	};

	struct ConstantBufferLayout
	{
		ShaderBufferDesc Description;
		TArray<ShaderVariableDesc> Variables;
		TArray<ShaderTypeDesc> Types;
		TArray<MX11RenderParameter*> Parameters;
		MX11RenderParameter* pParamRef;
	};

	class MX11Shader
	{
	public:
		MX11Shader();
		virtual ~MX11Shader();

		virtual ShaderType GetType() = 0;

		void UpdateParameters(MX11PipelineManager* pPipeline, IParamaterManager* pParamManager);
		void BindParameters(MX11PipelineManager* pPipeline, IParamaterManager* pParamManager);

	public:
		std::wstring FileName;
		ID3DBlob*	CompiledShader;
		D3D11_SHADER_DESC Desc;
		TArray<SignatureParameterDesc>	InputSignatureParameters;
		TArray<SignatureParameterDesc>	OutputSignatureParameters;
		TArray<ShaderInputBindDesc>		ResourceBindings;
		TArray<ConstantBufferLayout>	ConstantBuffers;

	protected:
		
	};
}