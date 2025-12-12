#include "pch.h"
#include "CMyBit.h"

CMyBit::CMyBit()
{
}

CMyBit::~CMyBit()
{
	Release();
}

void CMyBit::Load_Bmp(wstring FilePath)
{
	HDC hdc = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hdc);
	ReleaseDC(g_hWnd, hdc);

	m_hBit = (HBITMAP)LoadImage(NULL,
		FilePath.c_str(),
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBit);

}

void CMyBit::Load_AlphaBmp(wstring FilePath)
{
    HDC hdc = GetDC(g_hWnd);
    m_hMemDC = CreateCompatibleDC(hdc);

    HBITMAP hOriginalBmp = (HBITMAP)LoadImageW(NULL,
        FilePath.c_str(),
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION); // DIBSection으로 로드

    if (hOriginalBmp == nullptr)
    {
        ReleaseDC(g_hWnd, hdc);
        return;
    }

    // 3. 원본 비트맵 정보 가져오기 (지역 변수로 저장)
    BITMAP bmpInfo;
    GetObject(hOriginalBmp, sizeof(BITMAP), &bmpInfo);

    int iWidth = bmpInfo.bmWidth;
    int iHeight = bmpInfo.bmHeight;

    // 32비트 DIB 생성 준비
    BITMAPINFOHEADER bih = {};
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = iWidth;        // 지역 변수 사용
    bih.biHeight = -iHeight;     // 지역 변수 사용
    bih.biPlanes = 1;
    bih.biBitCount = 32;         // 32비트 포맷 (Alpha Channel 포함)
    bih.biCompression = BI_RGB;

    LPVOID lpBits; // 픽셀 데이터 포인터

    // 새 32비트 비트맵 생성 및 포인터 얻기
    HBITMAP hNewBit = CreateDIBSection(hdc, (BITMAPINFO*)&bih, DIB_RGB_COLORS, &lpBits, nullptr, 0);

    // 원본 데이터를 새 32비트 비트맵으로 복사
    HDC hTempSrcDC = CreateCompatibleDC(hdc);
    HDC hTempDestDC = CreateCompatibleDC(hdc);

    HBITMAP hOldSrcBit = (HBITMAP)SelectObject(hTempSrcDC, hOriginalBmp);
    HBITMAP hOldDestBit = (HBITMAP)SelectObject(hTempDestDC, hNewBit);

    // 24비트 -> 32비트 복사 (지역 변수 사용)
    BitBlt(hTempDestDC, 0, 0, iWidth, iHeight, hTempSrcDC, 0, 0, SRCCOPY);

    // 픽셀별 순회 및 알파 채널 설정 (마스킹)
    const BYTE R_KEY = 255;
    const BYTE G_KEY = 0;
    const BYTE B_KEY = 255; // 마젠타색 투명 키

    DWORD* pPixel = (DWORD*)lpBits;

    for (int y = 0; y < iHeight; ++y)
    {
        for (int x = 0; x < iWidth; ++x)
        {
            DWORD dwPixel = pPixel[y * iWidth + x];

            BYTE bR = GetRValue(dwPixel);
            BYTE bG = GetGValue(dwPixel);
            BYTE bB = GetBValue(dwPixel);

            if (bR == R_KEY && bG == G_KEY && bB == B_KEY)
            {
                pPixel[y * iWidth + x] &= 0x00FFFFFF; // 알파 0 (투명)
            }
            else
            {
                pPixel[y * iWidth + x] |= 0xFF000000; // 알파 255 (불투명)
            }
        }
    }

    // 사용한 임시 DC 및 비트맵 해제
    SelectObject(hTempSrcDC, hOldSrcBit);
    SelectObject(hTempDestDC, hOldDestBit);
    DeleteDC(hTempSrcDC);
    DeleteDC(hTempDestDC);
    DeleteObject(hOriginalBmp); // 원본 24비트 HBITMAP 해제

    // CMyBit 멤버 변수 업데이트
    m_hBit = hNewBit; // 32비트 비트맵으로 교체
    m_hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBit); // m_hMemDC에 새 비트맵 선택

    ReleaseDC(g_hWnd, hdc);
}



void CMyBit::Release()
{
	SelectObject(m_hMemDC, m_hOldBit);
	DeleteObject(m_hBit);
	DeleteDC(m_hMemDC);
}
