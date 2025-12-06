// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#include <ole2.h>   // IStream 정의
#include <gdiplus.h>

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")


//#include "fmod.h"
//#include "fmod.hpp"

//#pragma comment(lib, "fmodex_vc.lib")
#include <iostream>
#include <io.h>

#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
using namespace std;

#include "CObjMgr.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CMouse.h"
#include "CKeyMgr.h"
#include "CTileMgr.h"
#include "CLineMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CCollisionMgr.h"
#include "CUIMgr.h"
#include "CPlayerMgr.h"
#include "CAbstractFactory.h"

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif


#endif //PCH_H
