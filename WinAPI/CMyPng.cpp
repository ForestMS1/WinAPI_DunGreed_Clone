#include "pch.h"
#include "CMyPng.h"

CMyPng::CMyPng() : m_Img(nullptr)
{
}

CMyPng::~CMyPng()
{
	Safe_Delete(m_Img);
}


void CMyPng::Load_Image(wstring FilePath)
{
	m_Img = Image::FromFile(FilePath.c_str());
}
