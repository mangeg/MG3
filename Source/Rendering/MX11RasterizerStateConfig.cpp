//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11RasterizerStateConfig.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11RasterizerStateConfig::MX11RasterizerStateConfig()
{
	SetDefaults();
}
//------------------------------------------------------------------------|
MX11RasterizerStateConfig::~MX11RasterizerStateConfig()
{
}
//------------------------------------------------------------------------|
void MX11RasterizerStateConfig::SetDefaults()
{
	FillMode = D3D11_FILL_SOLID;
	CullMode = D3D11_CULL_BACK;
	FrontCounterClockwise = FALSE;
	DepthBias = 0;
	SlopeScaledDepthBias = 0.0f;
	DepthBiasClamp = 0.0f;
	DepthClipEnable = TRUE;
	ScissorEnable = FALSE;
	MultisampleEnable = FALSE;
	AntialiasedLineEnable = FALSE;
}