#include "pch.h"
#include "CLogo.h"
#include "CObjMgr.h"
#include "CPlayer.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, new CPlayer);

	CObjMgr::Get_Instance()->Initialize();
}

void CLogo::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CLogo::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CLogo::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CLogo::Release()
{
	CObjMgr::Get_Instance()->DeleteLayerObj(OBJ_PLAYER);
}
