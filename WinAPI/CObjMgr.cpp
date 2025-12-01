#include "pch.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"


CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Initialize()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjLayer[i].begin();
		for (; iter != m_ObjLayer[i].end(); ++iter)
		{
			(*iter)->Initialize();
		}
	}
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjLayer[i].begin();
			iter != m_ObjLayer[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjLayer[i].erase(iter);
			}
			else
			{
				iter++;
			}

		}

	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjLayer[i])
		{
			pObj->Late_Update();

			if (m_ObjLayer[i].empty())
				break;

			RENDERID	eID = pObj->Get_RenderID();
			m_RenderList[eID].push_back(pObj);

		}
	}

	//CCollisionMgr::Collision_Circle(m_ObjLayer[OBJ_BULLET], m_ObjLayer[OBJ_MONSTER]);

}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
			{
				return pDst->Get_Info()->fY < pSrc->Get_Info()->fY;
			});

		for (auto& pObj : m_RenderList[i])
		{
			pObj->Render(hDC);
		}

		m_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjLayer[i].begin();
		for (; iter != m_ObjLayer[i].end(); ++iter)
		{
			Safe_Delete((*iter));
		}
		m_ObjLayer[i].clear();
	}
}

void CObjMgr::AddObject(OBJ_LAYER eLayer, CObj* pObj)
{
	if (eLayer >= OBJ_END || pObj == nullptr)
		return;

	m_ObjLayer[eLayer].push_back(pObj);
}

void CObjMgr::DeleteLayerObj(OBJ_LAYER eLayer)
{
	list<CObj*>::iterator iter = m_ObjLayer[eLayer].begin();
	for (; iter != m_ObjLayer[eLayer].end(); ++iter)
	{
		Safe_Delete((*iter));
	}
	m_ObjLayer[eLayer].clear();
}
