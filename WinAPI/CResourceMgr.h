#pragma once
#include "Define.h"
#include "CMyBit.h"
#include "CMyPng.h"
class CResourceMgr
{
	SINGLE(CResourceMgr)

public:
	HDC Find_Bmp(wstring ImgKey);
	Image* Find_Png(wstring ImgKey);
	void Insert_Bmp(wstring FilePath, wstring ImgKey);
	void Insert_Png(wstring FilePath, wstring ImgKey);
	HBITMAP	FlipBitmapHorizontal(HBITMAP src);
	HBITMAP Get_Bmp(wstring ImgKey);
	void Release();


private:
	map<wstring, CMyBit*> m_mapBit;
	map<wstring, CMyPng*> m_mapImg;

};

