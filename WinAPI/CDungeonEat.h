#pragma once
#include "CNPC.h"
class CDungeonEat :
    public CNPC
{
public:
    CDungeonEat();
    ~CDungeonEat();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;


    bool CompleteEat() const { return m_bIsCompleteEat; }
private:
    bool m_bIsCompleteEat;
    bool m_bIsPlaySoundFirst;
    bool m_bIsPlaySoundSecond;
};

