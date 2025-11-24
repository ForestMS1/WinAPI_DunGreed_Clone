#pragma once
#include "CObj.h"
class CTile :
    public CObj
{
public:
    CTile();
    ~CTile();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void SetFrameKey(wstring ImgKey) { m_wsFrameKey = ImgKey; }
};

