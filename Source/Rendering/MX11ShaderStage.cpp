//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11ShaderStage.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
static void SetToNull( void* pArray, int num )
{
	const int ptrSize = sizeof( void* );
	memset( pArray, 0, num * ptrSize );
}
//------------------------------------------------------------------------|
MX11ShaderStage::MX11ShaderStage()
{
	for ( int i = 0; i < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; i++ ) ConstantBuffers[i] = 0;

	iCurrMaxCB = -1;
	iNextMaxCB = -1;
}
//------------------------------------------------------------------------|
MX11ShaderStage::~MX11ShaderStage()
{
};
//------------------------------------------------------------------------|
void MX11ShaderStage::SetCBuffer(int index, ID3D11Buffer* pBuffer)
{
	if ( index >= 0 && index < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT )
	{
		ConstantBuffers[index] = pBuffer;
		if(index > iNextMaxCB) iNextMaxCB = index;
		bBuffersDirty = true;
	}
}
//------------------------------------------------------------------------|
void MX11ShaderStage::BindResources(ID3D11DeviceContext* pContext)
{
	int index = -1;

	index = iNextMaxCB;
	if(index < iCurrMaxCB) index = iCurrMaxCB;

	if(index >= 0 && bBuffersDirty)
	{
		BindConstantBuffers(pContext, index + 1);

		iCurrMaxCB = iNextMaxCB;
		iNextMaxCB = -1;
		SetToNull(ConstantBuffers, index + 1);
		bBuffersDirty = false;
	}
}