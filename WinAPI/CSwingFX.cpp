#include "pch.h"
#include "CSwingFX.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CWeapon.h"
#include "CKeyMgr.h"
#include "CPlayer.h"

CSwingFX::CSwingFX()
{
	m_pOwner = nullptr;
}

CSwingFX::CSwingFX(CObj* pOwner)
{
	m_pOwner = pOwner;
}

CSwingFX::~CSwingFX()
{
	Release();
}

void CSwingFX::Initialize()
{
	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Effect/CosmosSwingFXTemp.png", L"CosmosSwordSwingFX");
	m_wsFrameKey = L"CosmosSwordSwingFX";
	m_iFrameWidth = 158.f;
	m_iFrameHeight = 181.f;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.dwSpeed = 50;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
}

int CSwingFX::Update()
{
	RECT* atr = dynamic_cast<CWeapon*>(m_pOwner)->Get_AttackRect();
	m_tRect.left = atr->left;
	m_tRect.top =  atr->top;
	m_tRect.right = atr->right;
	m_tRect.bottom = atr->bottom;

	m_tInfo.fX = m_tRect.left + m_tInfo.fCX * 0.5f;
	m_tInfo.fY = m_tRect.top + m_tInfo.fCY * 0.5f;


	

	CObj* pPlayer = dynamic_cast<CPlayer*>(dynamic_cast<CWeapon*>(m_pOwner)->Get_Owner());
	if (dynamic_cast<CPlayer*>(pPlayer)->Get_State() == CPlayer::ATTACK)
	{
		m_fAngle = dynamic_cast<CWeapon*>(m_pOwner)->Get_Angle();
		Move_Frame();
	}

	return 0;
}

void CSwingFX::Late_Update()
{
}

void CSwingFX::Render(HDC hDC)
{
	CObj* pPlayer = dynamic_cast<CWeapon*>(m_pOwner)->Get_Owner();
	if (dynamic_cast<CPlayer*>(pPlayer)->Get_State() == CPlayer::ATTACK)
	{
		Rectangle(
			hDC,
			m_tRect.left - GET(CCamera)->Get_ScrollX(),
			m_tRect.top - GET(CCamera)->Get_ScrollY(),
			m_tRect.right - GET(CCamera)->Get_ScrollX(),
			m_tRect.bottom - GET(CCamera)->Get_ScrollY());

		//1. 회전 시킬 사진을 비트맵으로 불러들인다..
		Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(L"CosmosSwordSwingFX");

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


		_matrix.RotateAt( - (m_fAngle * 180 / PI), PointF((float)(_tempBmp.GetWidth() / 2), (float)(_tempBmp.GetHeight() / 2)));

		//6. 5번의 좌표계를 2번에 세팅해서 DC를 회전시킨다.
		_tempgx.SetTransform(&_matrix);


		//7. 이미 돌아간 좌표계에 그림을 그리면 회전되어 그려진다.
		_tempgx.DrawImage(_bmp, 0, 0);


		//8. 회전되어 그려진 그림을 원하는 좌표에 그린다.
		_gx.DrawImage(
			&_tempBmp,
			//(int)(m_tInfo.fX - GET(CCamera)->Get_ScrollX() - _tempBmp.GetWidth() / 2),
			//(int)(m_tInfo.fY - GET(CCamera)->Get_ScrollY() - _tempBmp.GetHeight() / 2)
			(int)(m_tInfo.fX - GET(CCamera)->Get_ScrollX() - _tempBmp.GetWidth() / 2) + 167,
			(int)(m_tInfo.fY - GET(CCamera)->Get_ScrollY() - _tempBmp.GetHeight() / 2) + 90
		);
	}
}

void CSwingFX::Release()
{
}
