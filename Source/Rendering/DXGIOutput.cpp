//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "DXGIOutput.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
DXGIOutput::DXGIOutput(IDXGIOutput* pOutput)
{
	m_pOutput = pOutput;
	
	ZeroMemory(&m_Desc, sizeof(DXGI_OUTPUT_DESC));
	pOutput->GetDesc(&m_Desc);	
}
//------------------------------------------------------------------------|
DXGIOutput::~DXGIOutput()
{
	SAFE_RELEASE(m_pOutput);
}
//------------------------------------------------------------------------|
TCHAR* DXGIOutput::GetDeviceName()
{
	return m_Desc.DeviceName;
}
//------------------------------------------------------------------------|
DXGI_MODE_ROTATION DXGIOutput::GetRotation()
{
	return m_Desc.Rotation;
}
//------------------------------------------------------------------------|
RECT DXGIOutput::GetRect()
{
	return m_Desc.DesktopCoordinates;
}
//------------------------------------------------------------------------|
DXGI_OUTPUT_DESC DXGIOutput::GetDesc()
{	
	return m_Desc;
}