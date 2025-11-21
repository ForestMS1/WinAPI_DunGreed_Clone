#pragma once
#include "Define.h"
#include "CMyBit.h"
class CResourceMgr
{
	SINGLE(CResourceMgr)

public:
	HDC Find_Image(wstring ImgKey);
	void Insert_Image(wstring FilePath, wstring ImgKey);
	void Release();


private:
	map<wstring, CMyBit*> m_mapBit;

};

