#pragma once
#include "Define.h"
class CMyPng
{
public:
	CMyPng();
	~CMyPng();

	void Load_Image(wstring FilePath);
	Image* Get_Image() { return m_Img; }

private:
	Image* m_Img;
};

