#include "pch.h"
#include "CResourceMgr.h"
#include "CMyBit.h"

CResourceMgr* CResourceMgr::m_pInstance = nullptr;

CResourceMgr::CResourceMgr()
{

}
CResourceMgr::~CResourceMgr()
{
    Release();
}

HDC CResourceMgr::Find_Bmp(wstring ImgKey)
{
    if (m_mapBit.find(ImgKey) != m_mapBit.end())
        return m_mapBit[ImgKey]->Get_MemDC();

    return nullptr;
}

HBITMAP CResourceMgr::Get_Bmp(wstring ImgKey)
{
    if (m_mapBit.find(ImgKey) != m_mapBit.end())
        return m_mapBit[ImgKey]->Get_Bit();

    return nullptr;
}

Image* CResourceMgr::Find_Png(wstring ImgKey)
{
    if (m_mapImg.find(ImgKey) != m_mapImg.end())
        return m_mapImg[ImgKey]->Get_Image();
    return nullptr;
}

void CResourceMgr::Insert_Bmp(wstring FilePath, wstring ImgKey)
{
    if (m_mapBit.find(ImgKey) != m_mapBit.end())
        return;

    CMyBit* pBit = new CMyBit;
    pBit->Load_Bmp(FilePath);

    m_mapBit.insert({ ImgKey, pBit });
}

void CResourceMgr::Insert_Png(wstring FilePath, wstring ImgKey)
{
    if (m_mapImg.find(ImgKey) != m_mapImg.end())
        return;

    CMyPng* pPng = new CMyPng;
    pPng->Load_Image(FilePath);

    m_mapImg.insert({ ImgKey, pPng });
}

HBITMAP CResourceMgr::FlipBitmapHorizontal(HBITMAP src)
{
    BITMAP bm;
    GetObject(src, sizeof(bm), &bm);

    HDC hdc = GetDC(NULL);
    HDC srcDC = CreateCompatibleDC(hdc);
    HDC dstDC = CreateCompatibleDC(hdc);

    SelectObject(srcDC, src);

    HBITMAP dstBmp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
    HBITMAP oldDst = (HBITMAP)SelectObject(dstDC, dstBmp);

    StretchBlt(
        dstDC,
        0, 0,
        bm.bmWidth, bm.bmHeight,
        srcDC,
        bm.bmWidth - 1, 0,
        -bm.bmWidth, bm.bmHeight,
        SRCCOPY
    );

    SelectObject(dstDC, oldDst);
    DeleteDC(srcDC);
    DeleteDC(dstDC);
    ReleaseDC(NULL, hdc);

    return dstBmp; // ÁÂ¿ì¹ÝÀüµÈ ºñÆ®¸Ê
}

void CResourceMgr::Release()
{
    map<wstring, CMyBit*>::iterator iter = m_mapBit.begin();
    for (; iter != m_mapBit.end(); ++iter)
    {
        Safe_Delete(iter->second);
    }
    m_mapBit.clear();

    map<wstring, CMyPng*>::iterator iter2 = m_mapImg.begin();
    for (; iter2 != m_mapImg.end(); ++iter2)
    {
        Safe_Delete(iter2->second);
    }
    m_mapBit.clear();
}
