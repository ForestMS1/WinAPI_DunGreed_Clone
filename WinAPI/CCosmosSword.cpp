#include "pch.h"
#include "CCosmosSword.h"
#include "CResourceMgr.h"
#include "CCamera.h"

CCosmosSword::CCosmosSword(CObj* pOwner)
{
    m_pOwner = pOwner;
}
CCosmosSword::~CCosmosSword()
{

}

void CCosmosSword::Initialize()
{
    __super::Initialize();
    GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Weapon/CosmosSwordNoAnim.png", L"CosmosSword");
    m_fOffsetX = m_pOwner->Get_Info()->fCX * 0.5f;
    m_fOffsetY = m_pOwner->Get_Info()->fCY * 0.5f;

    m_tInfo.fX = m_pOwner->Get_Info()->fX + m_fOffsetX;
    m_tInfo.fY = m_pOwner->Get_Info()->fY - m_fOffsetY;
    m_iFrameWidth = 27;
    m_iFrameHeight = 81;
    m_tInfo.fCX = m_iFrameWidth;
    m_tInfo.fCY = m_iFrameHeight;

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 11;
    m_tFrame.dwSpeed = 100;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
}

int CCosmosSword::Update()
{
    CWeapon::Update();
	return 0;
}

void CCosmosSword::Late_Update()
{
    CWeapon::Late_Update();
}

void CCosmosSword::Render(HDC hDC)
{
    CWeapon::Render(hDC);

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



    //1. 회전 시킬 사진을 비트맵으로 불러들인다..
    Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(L"CosmosSword");

    //2. 이미지를 회전시켜도 잘리지 않을 정도의 크기로 빈 비트맵을 생성한다.
    Bitmap _tempBmp(_bmp->GetWidth(), _bmp->GetHeight());

    //3. 그려줄 것이므로 전체 화면 DC를 받아온다.
    //   ㄴ (더블버퍼를 위해 미리 만들어 둔 함수 사용)
    Graphics _gx(hDC);

    //4. 2번에서 생성한 비트맵의 사이즈에 맞는 DC를 받아온다.
    Graphics _tempgx(&_tempBmp);

    //5. 좌표계를 돌린다.
    //   ㄴ_angle만큼 돌려버린다.
    //     ㄴ radian이 아닌 degree 값.
    //   ㄴ PointF는 회전의 중심축이다.
    Matrix _matrix;

    _matrix.RotateAt(90 - (m_fAngle * 180 / PI), PointF((float)(_tempBmp.GetWidth()/2), (float)(_tempBmp.GetHeight()/2)));

    //6. 5번의 좌표계를 2번에 세팅해서 DC를 회전시킨다.
    _tempgx.SetTransform(&_matrix);


    //7. 이미 돌아간 좌표계에 그림을 그리면 회전되어 그려진다.
    _tempgx.DrawImage(_bmp, 0, 0);


    //8. 회전되어 그려진 그림을 원하는 좌표에 그린다.
    if (m_pOwner->IsFlipped())
    {
        _gx.DrawImage(
            &_tempBmp,
            (int)(m_tInfo.fX - GET(CCamera)->Get_ScrollX() - _tempBmp.GetWidth() / 2),
            (int)(m_tInfo.fY - GET(CCamera)->Get_ScrollY() - _tempBmp.GetHeight() / 2)
        );
    }
    else
    {
        _gx.DrawImage(
            &_tempBmp,
            (int)(m_tInfo.fX - GET(CCamera)->Get_ScrollX() - _tempBmp.GetWidth() / 2),
            (int)(m_tInfo.fY - GET(CCamera)->Get_ScrollY() - _tempBmp.GetHeight() / 2 + 30)
        );
    }

}

void CCosmosSword::Release()
{
}
