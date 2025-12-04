#include "pch.h"
#include "CCosmosSword.h"
#include "CResourceMgr.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSwingFX.h"

CCosmosSword::CCosmosSword(CObj* pOwner)
{
    m_pOwner = pOwner;
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
        m_pSwingFX = new CSwingFX(this);
        m_pSwingFX->Initialize();
    }
    GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Weapon/CosmosSwordNoAnim.png", L"CosmosSword");
    GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Weapon/LightSaber.png", L"LightSaber");
    m_fOffsetX = m_pOwner->Get_Info()->fCX * 0.5f;
    m_fOffsetY = m_pOwner->Get_Info()->fCY * 0.5f;

    m_tInfo.fX = m_pOwner->Get_Info()->fX + m_fOffsetX;
    m_tInfo.fY = m_pOwner->Get_Info()->fY - m_fOffsetY;
    m_iFrameWidth = 12;
    m_iFrameHeight = 84;
    m_tInfo.fCX = m_iFrameWidth;
    m_tInfo.fCY = m_iFrameHeight;

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 11;
    m_tFrame.dwSpeed = 100;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();

    m_fDamage = 30.f;
    m_iMaxAttackCount = 1;
    m_iCurAttackCount = 0;


    m_tAttackInfo.fCX = 60.f;
    m_tAttackInfo.fCY = 90.f;
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

    if (dynamic_cast<CPlayer*>(m_pOwner)->Get_State() == CPlayer::ATTACK)
    {
        m_fAngle += 60;
        if (!m_pOwner->IsFlipped())
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
    //Rectangle(
    //    hDC, 
    //    m_tAttackRect.left- GET(CCamera)->Get_ScrollX(),
    //    m_tAttackRect.top - GET(CCamera)->Get_ScrollY(),
    //    m_tAttackRect.right - GET(CCamera)->Get_ScrollX(), 
    //    m_tAttackRect.bottom - GET(CCamera)->Get_ScrollY());
    //HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"CosmosSword");

    int SrcX = m_iFrameWidth * m_tFrame.iStart;
    int SrcY = m_iFrameHeight * m_tFrame.iMotion;

    //GdiTransparentBlt(
    //    hDC,
    //    m_tRect.left - GET(CCamera)->Get_ScrollX(),
    //    m_tRect.top - GET(CCamera)->Get_ScrollY(),
    //    m_tInfo.fCX,
    //    m_tInfo.fCY,
    //    hMemDC,
    //    SrcX,
    //    SrcY,
    //    m_iFrameWidth,
    //    m_iFrameHeight,
    //    RGB(255, 0, 255)
    //);
    // 
 //-------------------------------------------------------------------------
    ////1. 회전 시킬 사진을 비트맵으로 불러들인다..
    //Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(L"CosmosSword");

    ////2. 이미지를 회전시켜도 잘리지 않을 정도의 크기로 빈 비트맵을 생성한다.
    //Bitmap _tempBmp(_bmp->GetWidth(), _bmp->GetHeight());

    ////3. 그려줄 것이므로 전체 화면 DC를 받아온다.
    ////   ㄴ (더블버퍼를 위해 미리 만들어 둔 함수 사용)
    //Graphics _gx(hDC);

    ////4. 2번에서 생성한 비트맵의 사이즈에 맞는 DC를 받아온다.
    //Graphics _tempgx(&_tempBmp);

    ////5. 좌표계를 돌린다.
    ////   ㄴ_angle만큼 돌려버린다.
    ////     ㄴ radian이 아닌 degree 값.
    ////   ㄴ PointF는 회전의 중심축이다.
    //Matrix _matrix;
    //

    //_matrix.RotateAt(90 - (m_fAngle * 180 / PI), PointF((float)(_tempBmp.GetWidth()/2), (float)(_tempBmp.GetHeight()/2)));

    ////6. 5번의 좌표계를 2번에 세팅해서 DC를 회전시킨다.
    //_tempgx.SetTransform(&_matrix);


    ////7. 이미 돌아간 좌표계에 그림을 그리면 회전되어 그려진다.
    //_tempgx.DrawImage(_bmp, 0, 0);


    ////8. 회전되어 그려진 그림을 원하는 좌표에 그린다.
    //if (m_pOwner->IsFlipped())
    //{
    //    _gx.DrawImage(
    //        &_tempBmp,
    //        (int)(m_tInfo.fX - GET(CCamera)->Get_ScrollX() - _tempBmp.GetWidth() / 2),
    //        (int)(m_tInfo.fY - GET(CCamera)->Get_ScrollY() - _tempBmp.GetHeight() / 2)
    //    );
    //}
    //else
    //{
    //    _gx.DrawImage(
    //        &_tempBmp,
    //        (int)(m_tInfo.fX - GET(CCamera)->Get_ScrollX() - _tempBmp.GetWidth() / 2),
    //        (int)(m_tInfo.fY - GET(CCamera)->Get_ScrollY() - _tempBmp.GetHeight() / 2 + 30)
    //    );
    //}

//----------------------------------------------------------------------------------------------------
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
    if (m_pOwner->IsFlipped())
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
}
