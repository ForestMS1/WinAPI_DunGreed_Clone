#pragma once
#include "Define.h"
class CMyBit
{
public:
	CMyBit();
	~CMyBit();

public:
	HDC		Get_MemDC() const { return m_hMemDC; }
	void	Load_Bmp(wstring FilePath);
	void	Release();
	void	Load_AlphaBmp(wstring FilePath);

private:
	HDC		m_hMemDC;

	HBITMAP m_hBit;
	HBITMAP m_hOldBit;
};

