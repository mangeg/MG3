//------------------------------------------------------------------------|
#include "DXGIAdapter.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
DXGIAdapter::DXGIAdapter(IDXGIAdapter1* pAdapter)
{
	m_pAdapter = pAdapter;
	
	m_pAdapter->GetDesc1(&m_Desc);
}
//------------------------------------------------------------------------|
DXGIAdapter::~DXGIAdapter()
{
	SAFE_RELEASE(m_pAdapter)
}
//------------------------------------------------------------------------|
std::wstring DXGIAdapter::GetName()
{
	return std::wstring(m_Desc.Description);
}