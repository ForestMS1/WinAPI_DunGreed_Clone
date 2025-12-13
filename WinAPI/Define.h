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

#define TILECX 64		// 실제 게임의 타일 사이즈
#define TILECY 64
#define BMPTILECX 16	// BMP 사진 파일의 타일 사이즈
#define BMPTILECY 16 
#define TILEX 100		// 게임에 깔 전체 타일 개수
#define TILEY 100

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

enum OBJ_LAYER{ OBJ_PLAYER, OBJ_PLAYER_BULLET, OBJ_ENEMY_BULLET, OBJ_MONSTER, OBJ_NPC, OBJ_DOOR, OBJ_EFFECT, OBJ_ITEM, OBJ_END };

enum SCENEID{ SCENE_LOGO, SCENE_TEST, SCENE_MAPTOOL,
	SCENE_DUNGEON_START,
	SCENE_DUNGEON_01,
	SCENE_DUNGEON_02,
	SCENE_DUNGEON_FOOD_SHOP,
	SCENE_DUNGEON_03,
	SCENE_DUNGEON_04,
	SCENE_DUNGEON_05,
	SCENE_DUNGEON_06,
	SCENE_DUNGEON_07,
	SCENE_DUNGEON_08,
	SCENE_DUNGEON_09,
	SCENE_ICE_DUNGEON_01,
	SCENE_ICE_DUNGEON_02,
	SCENE_NIFLEHEIM,
	SCENE_BELIAL, SCENE_END};

enum TILE_OPTION{ ERASE, BLOCKED, BLOCKED_UPHILL, BLOCKED_DOWNHILL, SPACIOUS, SPACIOUS_UPHILL, SPACIOUS_DOWNHILL, BACKGROUND, END };

enum RENDERID { BACK, GAMEOBJECT, BULLET, PLAYER, EFFECT, UI, RENDER_END };

enum CHANNELID { SOUND_BGM, SOUND_PLAYER_WALK , SOUND_PLAYER_MOVE, 
	SOUND_PLAYER_ATTACK1,
	SOUND_PLAYER_ATTACK2,
	SOUND_PLAYER_ATTACK3,
	SOUND_PLAYER_ATTACK4,
	SOUND_PLAYER_ATTACK5,
	SOUND_PLAYER_ATTACK6,
	SOUND_ENEMY_ATTACK,
	SOUND_EFFECT, MAXCHANNEL };

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

typedef struct tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

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