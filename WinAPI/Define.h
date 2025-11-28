#pragma once
#define WINCX 800
#define WINCY 640
//1920 //1080
//1280 //720
//720  //480
//800  //600
//800  //640

#define PURE = 0

#define PI 3.14592f
#define GRAVITY 9.8f

#define TILECX 32		// 실제 게임의 타일 사이즈
#define TILECY 32
#define BMPTILECX 16	// BMP 사진 파일의 타일 사이즈
#define BMPTILECY 16 
#define TILEX 300
#define TILEY 300

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
#define DT		CTimeMgr::Get_Instance()->GetDeltaTime()

enum OBJ_LAYER{ OBJ_PLAYER, OBJ_MONSTER, OBJ_ITEM, OBJ_END };

enum TILE_OPTION{ ERASE, BLOCKED, BLOCKED_UPHILL, BLOCKED_DOWNHILL, SPACIOUS, SPACIOUS_UPHILL, SPACIOUS_DOWNHILL, BACKGROUND, END };

typedef struct tagInfo
{
	float fX, fY; // 중심좌표
	float fCX, fCY; // 가로 세로 길이
}INFO;

typedef struct tagFrame
{
	int		iStart;
	int		iEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;

typedef struct tagTileInfo
{
	int iDrawIDX;
	int iDrawIDY;
}TILEINFO;

typedef struct Vec2
{
	float fX;
	float fY;

	Vec2(float _fX = 0, float _fY = 0)	{ fX = _fX; fY = _fY; }
	Vec2(POINT pt)						{ fX = (float)pt.x; fY = (float)pt.y; }

	Vec2 operator- (const Vec2& rhs)
	{
		return Vec2(fX - rhs.fX, fY - rhs.fY);
	}
	Vec2 operator- (const POINT& rhs)
	{
		return Vec2(fX - (float)rhs.x, fY - (float)rhs.y);
	}
	Vec2 operator+ (const Vec2& rhs)
	{
		return Vec2(fX + rhs.fX, fY + rhs.fY);
	}
	Vec2 operator+ (const POINT& rhs)
	{
		return Vec2(fX + (float)rhs.x, fY + (float)rhs.y);
	}
	Vec2& operator=(const Vec2& rhs)
	{
		fX = rhs.fX;
		fY = rhs.fY;
		return *this;
	}
	Vec2& operator+=(const Vec2& rhs)
	{
		fX += rhs.fX;
		fY += rhs.fY;
		return *this;
	}
	Vec2& operator=(const POINT& rhs)
	{
		fX = (float)rhs.x;
		fY = (float)rhs.y;
		return *this;
	}
	Vec2& operator+=(const POINT& rhs)
	{
		fX += (float)rhs.x;
		fY += (float)rhs.y;
		return *this;
	}
	Vec2 operator*(float scalar) const
	{
		return Vec2(fX * scalar, fY * scalar);
	}
	Vec2 operator*(int scalar) const
	{
		return Vec2(fX * (float)scalar, fY * (float)scalar);
	}
public:
	Vec2 Normalize()
	{
		float fDiagonal = sqrtf(fX * fX + fY * fY);
		if (fDiagonal == 0.f)
			return Vec2(0.f, 0.f);

		float x = fX / fDiagonal;
		float y = fY / fDiagonal;
		return Vec2(x, y);
	}
	float Length()
	{
		return sqrtf(fX * fX + fY * fY);
	}
}Vec2;

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
extern bool g_bDebugMod;