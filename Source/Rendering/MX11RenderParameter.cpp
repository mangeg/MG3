//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "MX11RenderParameter.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
MX11RenderParameter::MX11RenderParameter()
	: m_Ident(HashedString(L""))
{
}
//------------------------------------------------------------------------|
MX11RenderParameter::MX11RenderParameter(MX11RenderParameter& copy)
	: m_Ident(copy.m_Ident)
{
}
//------------------------------------------------------------------------|
MX11RenderParameter::~MX11RenderParameter()
{
}
//------------------------------------------------------------------------|
void MX11RenderParameter::SetIdent(const HashedString& ident)
{
	m_Ident = ident;
}
//------------------------------------------------------------------------|
HashedString& MX11RenderParameter::GetIdent()	
{	
	return m_Ident;
}