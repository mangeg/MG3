//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "DXGIOutput.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
DXGIOutput::DXGIOutput(IDXGIOutput* pOutput)
{
	m_pOutput = pOutput;
}
//------------------------------------------------------------------------|
DXGIOutput::~DXGIOutput()
{
	SAFE_RELEASE(m_pOutput);
}