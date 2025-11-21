#include "pch.h"
#include "CMyPng.h"

CMyPng::CMyPng()
{
}

CMyPng::~CMyPng()
{
}


void CMyPng::Load_Image(wstring FilePath)
{
	m_Img = Image::FromFile(FilePath.c_str());
}
