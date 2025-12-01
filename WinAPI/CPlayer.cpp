#include "pch.h"
#include "CPlayer.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CCollisionMgr.h"
#include "CTileMgr.h"
#include "CLineMgr.h"
#include "CCosmosSword.h"
#include "CMouse.h"
CPlayer::CPlayer() : 
	m_v0(0.f), m_ft(0.f), m_fAcct(3.f), m_bJump(false), m_bBottomJump(false), m_bIsGround(false), 
	m_fDasht(0.f), m_fDashAcct(0.3f), m_fDashSpeed(60.f), m_bDash(false), m_IsOnLine(false), m_IsOnBlock(false),
	m_bAttack(false), m_fAttackAcct(0.2f), m_fAttackt(0.f)
{
	m_pWeapon = nullptr;
	m_pRunEffect = nullptr;
}
CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_fSpeed = 7.f;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;
	m_tInfo.fCX = 45.f;
	m_tInfo.fCY = 60.f;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_wsFrameKey = L"Player";

	m_eRender = PLAYER;

	m_eCurState = IDLE;

	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/PlayerIdle.bmp", L"PlayerIdle");
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/PlayerJump.bmp", L"PlayerJump");
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/PlayerRun.bmp", L"PlayerRun");
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/PlayerDashR.bmp", L"PlayerDashR");
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/PlayerDashL.bmp", L"PlayerDashL");
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/RunEffectR.bmp", L"RunEffectR");
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/RunEffectL.bmp", L"RunEffectL");
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Unit/Player/PlayerDie.bmp", L"PlayerDie");

	//무기
	m_pWeapon = new CCosmosSword(this);
	//이펙트
	m_pRunEffect = new CRunEffect(this);

	m_vecOwned.push_back(m_pWeapon);
	m_vecOwned.push_back(m_pRunEffect);

	for (auto& pOwned : m_vecOwned)
	{
		if (pOwned)
		{
			pOwned->Initialize();
		}
	}
}

int CPlayer::Update()
{
	if (!(m_bJump || m_bDash))
		m_tInfo.fY += GRAVITY;

	m_bIsFlipped = ToMouse();


	Key_Input();

	Jump();
	Dash();
	Attack();

	Update_Rect();

	Move_Frame();

	for (auto& pOwned : m_vecOwned)
	{
		if (pOwned)
		{
			pOwned->Update();
		}
	}
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	float fOnLine(0.f), fDist(0.f);

	//하향 점프 버튼이 눌렸을때 or 대쉬중엔 순간적으로 선 충돌을 잠시 끈다
	if (!(m_bBottomJump || m_bDash))
		m_IsOnLine = GET(CLineMgr)->Collision_Line(this, &fOnLine);

	m_IsOnBlock = CCollisionMgr::Collision_RectTile(this, GET(CTileMgr)->GetVecTile());

	if (m_IsOnLine || m_IsOnBlock)
		m_bIsGround = true;
	else
	{
		m_bIsGround = false;
		m_eCurState = JUMP;
	}

	for (auto& pOwned : m_vecOwned)
	{
		if (pOwned)
		{
			pOwned->Late_Update();
		}
	}

#ifdef _DEBUG
	if (GET(CKeyMgr)->Key_Pressing(VK_RETURN))
	{
		system("cls");
		Vec2 rp = GET(CCamera)->GetRealPos(Vec2(m_tInfo.fX, m_tInfo.fY));
		Vec2 renderPos = GET(CCamera)->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
		cout << "플레이어 실제 위치 : " << rp.fX << "\t" << rp.fY << endl;
		cout << "플레이어 렌더 위치 : " << renderPos.fX << "\t" << renderPos.fY << endl;
		cout << "IsGround : " << m_bIsGround << "\t" << "IsOnLine : " << m_IsOnLine << "\t" << "IsOnBlock : " << m_IsOnBlock << endl;
		cout << m_eCurState;
	}
#endif // _DEBUG

	Motion_Change();
}

void CPlayer::Render(HDC hDC)
{
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(m_wsFrameKey);

	int SrcX = m_iFrameWidth * m_tFrame.iStart;
	int SrcY = m_iFrameHeight * m_tFrame.iMotion;

	if (g_bDebugMod)
	{
		Rectangle(hDC,
			m_tRect.left - GET(CCamera)->Get_ScrollX(),
			m_tRect.top - GET(CCamera)->Get_ScrollY(),
			m_tRect.right - GET(CCamera)->Get_ScrollX(),
			m_tRect.bottom - GET(CCamera)->Get_ScrollY());
	}
	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left - GET(CCamera)->Get_ScrollX() - 15),			// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top - GET(CCamera)->Get_ScrollY()),				// 복사 받을 공간의 TOP
		m_iFrameWidth,													// 복사 받을 공간의 가로 
		m_iFrameHeight,													// 복사 받을 공간의 세로 
		hMemDC,															// 복사 할 DC
		SrcX,															// 원본이미지 left
		SrcY,															// 원본이미지 top
		m_iFrameWidth,													// 원본이미지 가로
		m_iFrameHeight,													// 원본이미지 세로
		RGB(255, 0, 255)
	);

	for (auto& pOwned : m_vecOwned)
	{
		if (pOwned)
		{
			pOwned->Render(hDC);
		}
	}
}

void CPlayer::Release()
{
	for (auto& pOwned : m_vecOwned)
	{
		Safe_Delete(pOwned);
	}
}

void CPlayer::Key_Input()
{

	if (GET(CKeyMgr)->Key_Pressing('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;
	}
	else if (GET(CKeyMgr)->Key_Pressing('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;
	}
	else
	{
		m_eCurState = IDLE;
	}

	if (GET(CKeyMgr)->Key_Pressing('S'))
	{
		if (GET(CKeyMgr)->Key_Down(VK_SPACE))
		{
			m_bBottomJump = true;
			m_eCurState = JUMP;
		}
	}
	else
	{
		if (GET(CKeyMgr)->Key_Down(VK_SPACE))
		{
			m_v0 = 30.f;
			m_bJump = true;
			m_eCurState = JUMP;
			
		}
	}

	if (GET(CKeyMgr)->Key_Up(VK_SPACE))
	{
		m_bBottomJump = false;
	}

	if (GET(CKeyMgr)->Key_Down(VK_RBUTTON))
	{
		m_bDash = true;
		m_vDashDir = GET(CCamera)->GetRealPos(GET(CMouse)->Get_Point());
	}
	if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		m_bAttack = true;
	}
}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"PlayerIdle";
			m_iFrameWidth = 78;
			m_iFrameHeight = 60;
			break;

		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"PlayerRun";
			m_iFrameWidth = 78;
			m_iFrameHeight = 60;
			break;
		case JUMP:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"PlayerJump";
			m_iFrameWidth = 75;
			m_iFrameHeight = 60;
			break;
		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"PlayerDie";
			m_iFrameWidth = 78;
			m_iFrameHeight = 60;
			break;
		default:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"PlayerIdle";
			m_iFrameWidth = 78;
			m_iFrameHeight = 60;
			break;
		}

		m_ePreState = m_eCurState;
	}

}

void CPlayer::Jump()
{
	if (m_bJump && m_ft < m_fDashAcct)
	{
		m_ft += 0.01f;
		if (m_ft >= 0.4f)
			m_tInfo.fY -= m_v0 * (m_fDashAcct - m_fDasht) + 2 - (7 * 0.5f) * m_ft * m_ft;
		else
			m_tInfo.fY -= m_v0 * (0.4-m_ft);
		m_eCurState = JUMP;
	}
	else
	{
		m_ft = 0.f;
		m_bJump = false;
	}
}

void CPlayer::Dash()
{
	float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);


	fWidth = m_vDashDir.fX - m_tInfo.fX;
	fHeight = m_vDashDir.fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	if (m_vDashDir.fY > m_tInfo.fY)
		fRadian = 2.f * PI - fRadian;

	if (m_bDash && m_fDasht < m_fDashAcct)
	{
		m_fDasht += 0.01f;
		m_tInfo.fX += m_fDashSpeed * cosf(fRadian) * (m_fDashAcct - m_fDasht);
			if (!(m_IsOnBlock && sinf(fRadian) < 0))
				m_tInfo.fY -= m_fDashSpeed * sinf(fRadian) * (m_fDashAcct - m_fDasht);



	}
	else
	{
		m_fDasht = 0.f;
		m_bDash = false;
	}
}

void CPlayer::Attack()
{
	if (m_bAttack && m_fAttackt < m_fAttackAcct)
	{
		m_fAttackt += 0.01f;
		m_eCurState = ATTACK;
	}
	else
	{
		m_fAttackt = 0.f;
		m_bAttack = false;
	}
}

bool CPlayer::ToMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	Vec2 pos = GET(CCamera)->GetRealPos(Vec2((int)pt.x, (int)pt.y));
	if (pos.fX < m_tInfo.fX)
	{
		m_tFrame.iMotion = 1;
		return true;
	}
	else
	{
		m_tFrame.iMotion = 0;
		return false;
	}

	//TODO : 마우스 방향으로 무기회전
}