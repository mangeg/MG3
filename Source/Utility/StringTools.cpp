//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "StringTools.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
StringTools::StringTools()
{
}
//------------------------------------------------------------------------|
std::string StringTools::ToAscii(std::wstring& txt)
{
	std::string temp(txt.length(), ' ');
	std::copy(txt.begin(), txt.end(), temp.begin());
	return temp;
}
//------------------------------------------------------------------------|
std::wstring StringTools::ToUnicode(std::string& txt)
{	
	std::wstring temp(txt.length(), L' ');
	std::copy(txt.begin(), txt.end(), temp.begin());
	return temp;
}