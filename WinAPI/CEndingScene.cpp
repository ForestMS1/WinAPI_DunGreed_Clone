#include "pch.h"
#include "CEndingScene.h"
#include "CPlayer.h"
#include "CNPC_Xmas.h"
#include "CFairyXL.h"
#include "CPresent.h"
#include "CSnow.h"
CEndingScene::CEndingScene() : m_bAlpha(0), m_fTextScrollY(-150.f), m_fSpeed(1.f)
{
}

CEndingScene::~CEndingScene()
{
	Release();
}

void CEndingScene::Initialize()
{

	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(325, 890));
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CNPC_Xmas>::Create(175, 1050)); //간격 150..
	CItem* pFairy = new CFairyXL(100, 230, 1150);
	pFairy->SetDrop(true);
	pFairy->Initialize();
	GET(CObjMgr)->AddObject(OBJ_ITEM, pFairy);
	CSnow* pSnow = new CSnow;
	pSnow->Initialize();
	GET(CObjMgr)->AddObject(OBJ_EFFECT, pSnow);
	//GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CPresent>::Create(125, 1050));

	GET(CPlayerMgr)->Initialize();

	GET(CObjMgr)->Initialize();
	pSnow->SetSpeed(3.f);
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"Ending");

	//GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	//GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();


	GET(CResourceMgr)->Insert_AlphaBmp(L"../Resources/Images/UI/Logo.bmp", L"LogoAlpha");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Ending/Jusin.bmp", L"Jusin");
	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Ending/SwingChair.png", L"SwingChair");
	//GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Bird.bmp", L"Bird");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Sky.bmp", L"Sky");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Cloud2.bmp", L"Cloud2");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Cloud.bmp", L"Cloud");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Ending/TownSky_Xmas.bmp", L"TownSky_Xmas");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownBG_Day.bmp", L"TownBG_Day");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/NPC/Present.bmp", L"Present");


	GET(CCamera)->SetTarget(nullptr);
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1 - 2000));

	GET(CSoundMgr)->PlayBGM(L"Ending.wav", 1.f);
	m_SpawnEffectStartTime = GetTickCount();

	AddFontResource(TEXT("Aa카시오페아"));
	m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

void CEndingScene::Update()
{
	GET(CCamera)->SetLookAt(Vec2(420, 890));

	DWORD dwCurrentTime = GetTickCount();
	DWORD dwElapsedTime = dwCurrentTime - m_SpawnEffectStartTime;

	if (dwElapsedTime < 3500)
		m_bAlpha = (BYTE)(((float)dwElapsedTime / 3500) * 255.f);

	m_fTextScrollY += m_fSpeed;
}

void CEndingScene::Late_Update()
{
}

void CEndingScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	HDC hTownDC = GET(CResourceMgr)->Find_Bmp(L"TownSky_Xmas");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hTownDC,
		0,
		0,
		320,
		180,
		RGB(255, 0, 255));

	HDC hTownBGDC = GET(CResourceMgr)->Find_Bmp(L"TownBG_Day");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hTownBGDC,
		0,
		0,
		320,
		142,
		RGB(255, 0, 255));
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	HDC hPresentDC = GET(CResourceMgr)->Find_Bmp(L"Present");
	GdiTransparentBlt(
		hDC,
		125 - 24 - scrollX,
		1065 - 21 - scrollY,
		48,
		42,
		hPresentDC,
		0,
		0,
		16,
		14,
		RGB(255, 0, 255));

	HDC hLogoDC = GET(CResourceMgr)->Find_Bmp(L"LogoAlpha");

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;					// 일반적인 소스 오버 블렌딩
	bf.BlendFlags = 0;							// 예약 필드 (0으로 설정)
	bf.SourceConstantAlpha = m_bAlpha;			// 우리가 설정한 불투명도 값 (0~255)
	bf.AlphaFormat = AC_SRC_ALPHA;				// 알파 채널이 비트맵 자체에 없을 경우 (Constant Alpha 사용)


	AlphaBlend(
		hDC, // 대상 HDC
		(WINCX >> 1) - 234 - 150,
		(WINCY >> 1) - 225,
		468,
		225,
		hLogoDC,                 
		0,
		0,
		468,
		225,
		bf
	);

	float offsetX = 100;
	float offsetY = 50;
	HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);
	wstring text = L"김성윤 : 스커지 브링어";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY, text.c_str(), (int)text.size());
	text = L"최광윤 : 할로우나이트 실크송";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY, text.c_str(), (int)text.size());
	text = L"김종진 : 네크로댄서";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY*2, text.c_str(), (int)text.size());
	text = L"이창준 : 엔터더건전";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 3, text.c_str(), (int)text.size());
	text = L"권지현 : 던그리드";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 4, text.c_str(), (int)text.size());
	text = L"김민수 : 스펠렁키2";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 5, text.c_str(), (int)text.size());
	text = L"임성윤 : 산나비";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 6, text.c_str(), (int)text.size());
	text = L"이성민 : 크레이지아케이드";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 7, text.c_str(), (int)text.size());
	text = L"이호영 : 1945";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 8, text.c_str(), (int)text.size());
	text = L"김대성 : 던그리드";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 9, text.c_str(), (int)text.size());

	text = L"시청해 주셔서 감사합니다.";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 12, text.c_str(), (int)text.size());

	text = L"160기 다들 고생 많으셨습니다!!";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	TextOut(hDC, WINCX - 200 - offsetX, WINCY - m_fTextScrollY + offsetY * 13, text.c_str(), (int)text.size());

	HDC hJusinDC = GET(CResourceMgr)->Find_Bmp(L"Jusin");
	GdiTransparentBlt(
		hDC,
		WINCX - 200 - offsetX,
		WINCY - m_fTextScrollY + offsetY * 14,
		218,
		174,
		hJusinDC,
		0,
		0,
		218,
		174,
		RGB(255, 0, 255));

	//text = to_wstring(m_pItem->GetShopPrice());
	//TextOut(hDC, m_tRect.left + 230, m_tRect.top + 35, text.c_str(), (int)text.size());
	SelectObject(hDC, hOldFont);
}

void CEndingScene::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CSoundMgr)->StopAll();

	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	RemoveFontResource(TEXT("Aa카시오페아"));
}
