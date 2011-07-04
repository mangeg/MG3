//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "DXGIAdapter.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
DXGIAdapter::DXGIAdapter(IDXGIAdapter1* pAdapter)
{
	m_pAdapter = pAdapter;
	
	m_pAdapter->GetDesc1(&m_Desc);

	IDXGIOutput* pOutput = 0;
	while ( pAdapter->EnumOutputs( m_vOutputs.Size(), &pOutput ) != DXGI_ERROR_NOT_FOUND )
	{
		m_vOutputs.Add( MG_NEW DXGIOutput( pOutput ) );
	}
}
//------------------------------------------------------------------------|
DXGIAdapter::~DXGIAdapter()
{
	for(int i = 0; i < m_vOutputs.Size(); i++)
		delete m_vOutputs[i];

	SAFE_RELEASE(m_pAdapter)
}
//------------------------------------------------------------------------|
std::wstring DXGIAdapter::GetName()
{
	return std::wstring(m_Desc.Description);
}