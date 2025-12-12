#include "pch.h"
#include "CNPC.h"
#include "CNPCKeyUI.h"
#include "CGold.h"

CNPC::CNPC() : m_fDetectfCX(0.f), m_fDetectfCY(0.f), m_bIsInPlayer(false)
, m_pKeyUI(nullptr)
{
	ZeroMemory(&m_tDetectRect, sizeof(RECT));
	m_eRender = GAMEOBJECT;
}

CNPC::~CNPC()
{
	Release();
}

void CNPC::Initialize()
{
	if (m_pKeyUI == nullptr)
		m_pKeyUI = new CNPCKeyUI(this);
	m_pKeyUI->Initialize();
}

int CNPC::Update()
{
	if (m_pKeyUI != nullptr)
		m_pKeyUI->Update();
	return 0;
}

void CNPC::Late_Update()
{
	if (m_pKeyUI != nullptr)
		m_pKeyUI->Late_Update();
}

void CNPC::Render(HDC hDC)
{
	if (m_pKeyUI != nullptr && m_bIsInPlayer)
		m_pKeyUI->Render(hDC);
}

void CNPC::Release()
{
	Safe_Delete(m_pKeyUI);
}

void CNPC::Update_DetectRect()
{
	m_tDetectRect.left = m_tInfo.fX - m_fDetectfCX * 0.5f;
	m_tDetectRect.top = m_tInfo.fY - m_fDetectfCY * 0.5f;
	m_tDetectRect.right = m_tInfo.fX + m_fDetectfCX * 0.5f;
	m_tDetectRect.bottom = m_tInfo.fY + m_fDetectfCY * 0.5f;
}

void CNPC::DropGold(int gold)
{

		//for (size_t i = 0; i < 5; ++i)
		//{
	CItem* pGold = new CGold(gold, m_tInfo.fX, m_tInfo.fY);
	pGold->SetDrop(true);
	pGold->Initialize();
	GET(CObjMgr)->AddObject(OBJ_ITEM, pGold);
		//}

}
