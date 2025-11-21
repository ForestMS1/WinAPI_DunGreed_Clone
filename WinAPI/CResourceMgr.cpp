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

HDC CResourceMgr::Find_Image(wstring ImgKey)
{
    if (m_mapBit.find(ImgKey) != m_mapBit.end())
        return m_mapBit[ImgKey]->Get_MemDC();

    return nullptr;
}

void CResourceMgr::Insert_Image(wstring FilePath, wstring ImgKey)
{
    if (m_mapBit.find(ImgKey) != m_mapBit.end())
        return;

    CMyBit* pBit = new CMyBit;
    pBit->Load_Bmp(FilePath);

    m_mapBit.insert({ ImgKey, pBit });
}

void CResourceMgr::Release()
{
    map<wstring, CMyBit*>::iterator iter = m_mapBit.begin();
    for (; iter != m_mapBit.end(); ++iter)
    {
        Safe_Delete(iter->second);
    }
    m_mapBit.clear();
}
