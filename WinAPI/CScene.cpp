#include "pch.h"
#include "CScene.h"
#include "CDoor.h"
CScene::CScene() : m_bIsClearScene(false)
{
}

CScene::~CScene()
{
}

void CScene::OpenDoor()
{
	if (GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty())
	{
		for (auto& iter : GET(CObjMgr)->GetObjLayer(OBJ_DOOR))
		{
			if (dynamic_cast<CDoor*>(iter)->GetDoorState() == CDoor::IDLE_LEFT)
				dynamic_cast<CDoor*>(iter)->SetDoorState(CDoor::OPEN_LEFT);
			else if (dynamic_cast<CDoor*>(iter)->GetDoorState() == CDoor::IDLE_BOTTOM)
				dynamic_cast<CDoor*>(iter)->SetDoorState(CDoor::OPEN_BOTTOM);
			else if (dynamic_cast<CDoor*>(iter)->GetDoorState() == CDoor::IDLE_RIGHT)
				dynamic_cast<CDoor*>(iter)->SetDoorState(CDoor::OPEN_RIGHT);
		}
	}
}

void CScene::DoorToNextScene()
{
	for (auto& iter : GET(CObjMgr)->GetObjLayer(OBJ_DOOR))
	{
		if ((dynamic_cast<CDoor*>(iter)->GetDoorState() == CDoor::DOOR_STATE::OPEN_LEFT
			|| dynamic_cast<CDoor*>(iter)->GetDoorState() == CDoor::DOOR_STATE::OPEN_BOTTOM
			|| dynamic_cast<CDoor*>(iter)->GetDoorState() == CDoor::DOOR_STATE::OPEN_RIGHT)
			&& CCollisionMgr::Check_Rect(GET(CPlayerMgr)->GetPlayer(), iter))
		{
			GET(CSceneMgr)->ChangeScene(dynamic_cast<CDoor*>(iter)->GetNextSceneName());
			break;
		}
	}
}
