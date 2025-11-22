#pragma once
#define WINCX 800
#define WINCY 600

#define PURE = 0

#define PI 3.14592f

#define	OBJ_NOEVENT 0
#define	OBJ_DEAD    1
#define VK_MAX		0xff
#define	SINGLE(T)					\
public:								\
	static T* Get_Instance()		\
	{								\
		if(m_pInstance == nullptr)	\
		{							\
			m_pInstance = new T;	\
		}							\
		return m_pInstance;			\
	}								\
	static void Destroy_Instance()	\
	{								\
		if (m_pInstance)			\
		{							\
			delete m_pInstance;		\
			m_pInstance = nullptr;	\
		}							\
	}								\
private:							\
	T();							\
	~T();							\
	T& operator=(T&) = delete;		\
	T(const T& rhs)	 = delete;		\
	static T* m_pInstance;			

#define GET(T)	T::Get_Instance()

enum OBJ_LAYER{ OBJ_PLAYER, OBJ_MONSTER, OBJ_ITEM, OBJ_END };

typedef struct tagInfo
{
	float fX, fY; // 중심좌표
	float fCX, fCY; // 가로 세로 길이
}INFO;

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}


extern HWND g_hWnd;