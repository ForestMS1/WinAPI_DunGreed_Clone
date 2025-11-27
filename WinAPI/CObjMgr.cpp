#include "pch.h"
#include "CObjMgr.h"


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
		list<CObj*>::iterator iter = m_ObjLayer[i].begin();
		for (; iter != m_ObjLayer[i].end(); ++iter)
		{
			(*iter)->Update();
		}
	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjLayer[i].begin();
		for (; iter != m_ObjLayer[i].end(); ++iter)
		{
			(*iter)->Late_Update();
		}
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjLayer[i].begin();
		for (; iter != m_ObjLayer[i].end(); ++iter)
		{
			(*iter)->Render(hDC);
		}
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
