#pragma once
#include "Define.h"
class CMyBit
{
public:
	CMyBit();
	~CMyBit();

public:
	HDC		Get_MemDC() const { return m_hMemDC; }
	HBITMAP	Get_Bit()	const { return m_hBit; }
	void	Load_Bmp(wstring FilePath);
	void	Release();

private:
	HDC		m_hMemDC;

	HBITMAP m_hBit;
	HBITMAP m_hOldBit;
};

