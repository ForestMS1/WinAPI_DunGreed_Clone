#include "pch.h"
#include "CSoundMgr.h"
#include <io.h>
#include <filesystem>

// FMOD C++ API를 사용하려면 fmod.hpp를 포함해야 합니다.
// (CSoundMgr.h 파일에 이미 포함되어 있을 가능성이 높지만 확인해 주세요)
#include "fmod.hpp" 
// FMOD C API를 사용할 때는 fmod.h만 필요하지만, 현재 코드는 C++ API의
// System_Create와 init 메서드 호출을 혼합 사용하고 있었습니다.

// FMOD C API 구조체를 C++ 네임스페이스로 변경
#define FMOD_SOUND FMOD::Sound
#define FMOD_CHANNEL FMOD::Channel
#define FMOD_SYSTEM FMOD::System

CSoundMgr* CSoundMgr::m_pInstance = nullptr;

// 생성자에서 m_pSystem을 nullptr로 초기화합니다. (FMOD C++ API 스타일)
CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr;
	// m_pChannelArr 배열도 초기화 필요
	for (int i = 0; i < MAXCHANNEL; ++i)
	{
		m_pChannelArr[i] = nullptr;
	}
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

void CSoundMgr::Initialize()
{
	// 💥 수정 1: FMOD_System_Create에 인수를 사용하지 않습니다.
	// FMOD::System_Create(&m_pSystem);
	// (FMOD C++ API를 사용하는 것이 안전하지만, 기존 변수 m_pSystem이 C API 타입이므로 일단 C API 함수를 인스턴스 없이 호출)
	// FMOD C API: FMOD_System_Create(&m_pSystem);
	// FMOD C++ API: FMOD::System_Create(&m_pSystem);

	// *주의: C++ API를 사용하도록 FMOD_SYSTEM 매크로를 정의했기 때문에 아래 코드를 사용합니다.
	FMOD::System_Create(&m_pSystem);


	// 💥 수정 2: FMOD_System_Init을 m_pSystem->init() 메서드로 변경합니다.
	// 1. 사용할 가상채널 수, 2. 초기화 방식, 3. NULL
	m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);

	LoadSoundFile();
}

void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		// TCHAR* 메모리 해제
		delete[] Mypair.first;

		// FMOD 사운드 해제
		if (Mypair.second)
		{
			Mypair.second->release(); // FMOD_Sound_Release 대신 C++ 메서드 사용
		}
	}
	m_mapSound.clear();

	// 시스템 종료 (Close) 후 해제 (Release)
	if (m_pSystem)
	{
		m_pSystem->close();
		m_pSystem->release();
	}
}


void CSoundMgr::PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(),
		[&](auto& iter)->bool
		{
			return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	bool bPlay = FALSE;

	// 현재 채널이 재생 중인지 확인
	if (m_pChannelArr[eID]) // 채널 객체가 생성되어 있어야 함
	{
		m_pChannelArr[eID]->isPlaying(&bPlay); // FMOD_Channel_IsPlaying 대신 C++ 메서드 사용
	}

	if (!bPlay) // eID 채널이 재생 중이 아닐 때만 재생
	{
		// 💥 수정 3: FMOD_CHANNEL_FREE 제거. FMOD 시스템이 자동으로 빈 채널을 할당합니다.
		m_pSystem->playSound(iter->second, nullptr, FALSE, &m_pChannelArr[eID]);

		// C API 버전: FMOD_System_PlaySound(m_pSystem, iter->second, FALSE, &m_pChannelArr[eID]);
	}

	// 볼륨 설정
	if (m_pChannelArr[eID])
	{
		m_pChannelArr[eID]->setVolume(fVolume); // FMOD_Channel_SetVolume 대신 C++ 메서드 사용
	}

	// ⚠️ 주의: Update는 게임 루프에서 한 번만 호출하는 것이 효율적입니다.
	// m_pSystem->update();
}

void CSoundMgr::PlayBGM(const TCHAR* pSoundKey, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(pSoundKey, iter.first);
		});

	if (iter == m_mapSound.end())
		return;

	// 💥 수정 4: FMOD_CHANNEL_FREE 제거.
	m_pSystem->playSound(iter->second, nullptr, FALSE, &m_pChannelArr[SOUND_BGM]);

	// 모드 설정 (BGM은 반복 재생)
	if (m_pChannelArr[SOUND_BGM])
	{
		m_pChannelArr[SOUND_BGM]->setMode(FMOD_LOOP_NORMAL);
		m_pChannelArr[SOUND_BGM]->setVolume(fVolume);
	}

	// ⚠️ 주의: Update는 게임 루프에서 한 번만 호출하는 것이 효율적입니다.
	// m_pSystem->update();
}

void CSoundMgr::StopSound(CHANNELID eID)
{
	if (m_pChannelArr[eID])
	{
		m_pChannelArr[eID]->stop(); // FMOD_Channel_Stop 대신 C++ 메서드 사용
	}
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
	{
		if (m_pChannelArr[i])
		{
			m_pChannelArr[i]->stop();
		}
	}
}

void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
{
	if (m_pChannelArr[eID])
	{
		m_pChannelArr[eID]->setVolume(fVolume);
	}

	// ⚠️ 주의: Update는 게임 루프에서 한 번만 호출하는 것이 효율적입니다.
	// m_pSystem->update();
}

void CSoundMgr::LoadSoundFile()
{
	_finddata_t fd;

	long long handle = _findfirst("../Resources/Sounds/*.*", &fd);

	if (handle == -1)
		return;

	int iResult = 0;

	char szCurPath[128] = "../Resources/Sounds/";
	char szFullPath[128] = "";

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath);

		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;

		// 💥 수정 5: FMOD_HARDWARE 제거 및 FMOD_System_CreateSound를 m_pSystem->createSound로 변경
		FMOD_RESULT eRes = m_pSystem->createSound(szFullPath, FMOD_DEFAULT, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.insert({ pSoundKey, pSound });
		}

		iResult = _findnext(handle, &fd);
	}

	// ⚠️ 주의: Update는 게임 루프에서 한 번만 호출하는 것이 효율적입니다.
	// m_pSystem->update();

	_findclose(handle);
}