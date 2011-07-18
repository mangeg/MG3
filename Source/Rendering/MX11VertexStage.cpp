//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11VertexStage.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11VertexStage::MX11VertexStage()
{
}
//------------------------------------------------------------------------|
MX11VertexStage::~MX11VertexStage()
{
}
//------------------------------------------------------------------------|
void MX11VertexStage::BindConstantBuffers( ID3D11DeviceContext* pContext, int count )
{
	pContext->VSSetConstantBuffers(0, count, ConstantBuffers);
}