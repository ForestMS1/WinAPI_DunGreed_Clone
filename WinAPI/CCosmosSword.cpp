#include "pch.h"
#include "CCosmosSword.h"
#include "CResourceMgr.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSwingFX.h"

CCosmosSword::CCosmosSword()
{
    m_pSwingFX = nullptr;
}
CCosmosSword::~CCosmosSword()
{
    Safe_Delete(m_pSwingFX);
}

void CCosmosSword::Initialize()
{
    __super::Initialize();
    if (m_pSwingFX == nullptr)
    {
        m_pSwingFX = new CSwingFX;
    }
    m_pSwingFX->Initialize();
    GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Weapon/CosmosSwordNoAnim.png", L"CosmosSword");
    GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Weapon/LightSaber.png", L"LightSaber");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Item/Weapon/LightSaber.bmp", L"LightSaber");
    m_fOffsetX = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fCX * 0.5f;
    m_fOffsetY = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fCY * 0.5f;

    m_tInfo.fX = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX + m_fOffsetX;
    m_tInfo.fY = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY - m_fOffsetY;
    m_iFrameWidth = 12;
    m_iFrameHeight = 84;
    m_tInfo.fCX = m_iFrameWidth;
    m_tInfo.fCY = m_iFrameHeight;

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 11;
    m_tFrame.dwSpeed = 100;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();

    m_fDamage = 10.f;
    m_iMaxAttackCount = 3;
    m_iCurAttackCount = 0;


    m_tAttackInfo.fCX = 60.f;
    m_tAttackInfo.fCY = 90.f;

    ZeroMemory(&m_tAttackRect, sizeof(RECT));
    m_wsFrameKey = L"LightSaber";
}

int CCosmosSword::Update()
{
    CWeapon::Update();
    if (m_pSwingFX != nullptr)
    {
        m_pSwingFX->Update();
    }
	return 0;
}

void CCosmosSword::Late_Update()
{
    CWeapon::Late_Update();

    //if (dynamic_cast<CPlayer*>(m_pOwner)->Get_State() == CPlayer::ATTACK)
    if (dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->Get_IsAttack())
    {
        m_fAngle += 60;
        if (!dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->IsFlipped())
        {
            
            m_tAttackRect =
            {
                m_tRect.right,
                m_tRect.top,
                m_tRect.right + 60,
                m_tRect.bottom
            };

            //m_tAttackInfo.fX = m_tInfo.fX;
            //m_tAttackInfo.fY = m_tInfo.fY;


        }
        else
        {
            m_fAngle += 270;
            m_tAttackRect =
            {
                m_tRect.left - 60,
                m_tRect.top,
                m_tRect.left,
                m_tRect.bottom
            };
            //m_tAttackInfo.fX = m_tInfo.fX + m_tInfo.fCX * 2.f;
            //m_tAttackInfo.fY = m_tInfo.fY;
        }
        for(int i = 0; i < m_iMaxAttackCount; ++i)
            GET(CSoundMgr)->PlaySoundW(L"LightSaber.wav", SOUND_EFFECT, 1.f);
        CCollisionMgr::Collision_Weapon(this, GET(CObjMgr)->GetObjLayer(OBJ_MONSTER));
    }
    else
    {
        m_iCurAttackCount = 0;
    }
    if (m_pSwingFX != nullptr)
    {
        m_pSwingFX->Late_Update();
    }
}

void CCosmosSword::Render(HDC hDC)
{
    CWeapon::Render(hDC);

    int SrcX = m_iFrameWidth * m_tFrame.iStart;
    int SrcY = m_iFrameHeight * m_tFrame.iMotion;

    int ScrollX = GET(CCamera)->Get_ScrollX();
    int ScrollY = GET(CCamera)->Get_ScrollY();

    // 1. 필요한 값 및 객체 준비
    Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(L"LightSaber");
    if (!_bmp) return;

    int W = _bmp->GetWidth();
    int H = _bmp->GetHeight();

    // 화면 DC Graphics 객체
    Graphics _gx(hDC);

    // 원본 이미지 중심 좌표 (회전의 중심축)
    float centerX = 6.f;//(float)W / 2.0f;
    float centerY = H;//(float)H / 2.0f;

    // 최종적으로 이미지가 그려질 화면상의 중심 좌표 (스크롤 및 Info 반영)
    float targetX = m_tInfo.fX - ScrollX;
    float targetY = m_tInfo.fY - ScrollY;

    // 2. 현재 Graphics의 변환 상태 저장
    Matrix originalMatrix;
    _gx.GetTransform(&originalMatrix); // 기존 행렬 저장 (복원용)

    // 3. 변환(Transform) 단계 적용

    // 3-1. 최종 위치로 이동 (targetX, targetY)
    _gx.TranslateTransform(targetX, targetY);

    // 3-2. 각도만큼 회전 (m_fAngle은 Degree라고 가정)
    float offset = 0.f;
    if (dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->IsFlipped())
        offset = 60.f;
    else
        offset = 0.f;
    _gx.RotateTransform(-(m_fAngle+270 + offset) * 180.f / PI);

    // 3-3. 원본 중심점을 원점으로 이동 (-centerX, -centerY)
    // 이 과정을 거쳐야 DrawImage(0, 0) 호출 시 원본 이미지의 중심이 
    // RotateTransform과 TranslateTransform의 최종 원점(targetX, targetY)에 위치하게 됩니다.
    _gx.TranslateTransform(-centerX, -centerY);


    // 4. 이미지 그리기
    // 변환된 좌표계의 (0, 0) 위치에 원본 이미지를 그립니다.
    _gx.DrawImage(_bmp, 0, 0);


    // 5. Graphics 변환 상태 복원 (매우 중요!)
    _gx.SetTransform(&originalMatrix);



    if (m_pSwingFX != nullptr)
    {
        m_pSwingFX->Render(hDC);
    }
}

void CCosmosSword::Release()
{
    Safe_Delete(m_pSwingFX);
}
