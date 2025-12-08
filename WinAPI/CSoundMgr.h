#pragma once
#include "Define.h"

// FMOD C++ API 사용을 위한 헤더 파일 포함
#include "fmod.hpp" 

class CSoundMgr
{
	SINGLE(CSoundMgr)
public:
	void Initialize();
	void Release();

public:
	void PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(const TCHAR* pSoundKey, float fVolume);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);
	void PlayQuadSound(const TCHAR* pSoundKey, float fVolume, DWORD delay);

public: // GetSystem 함수 추가 (main loop에서 update 호출용)
	FMOD::System* GetSystem() { return m_pSystem; }

private:
	void LoadSoundFile();

private:
	// 사운드 리소스 정보를 갖는 객체 (FMOD_SOUND -> FMOD::Sound*로 변경)
	std::map<TCHAR*, FMOD::Sound*> m_mapSound;
	// std::map을 사용하셨다면 #include <map> 이 필요할 수 있지만, 일반적으로 pch.h에 포함되어 있을 것입니다.

	// FMOD::Channel : 재생하고 있는 사운드를 관리할 객체 (FMOD_CHANNEL -> FMOD::Channel*로 변경)
	FMOD::Channel* m_pChannelArr[MAXCHANNEL];

	// 사운드, 채널 객체 및 장치를 관리하는 객체 (FMOD_SYSTEM -> FMOD::System*로 변경)
	FMOD::System* m_pSystem;
};

// *참고: 만약 C API를 고수하고 싶다면, .cpp 파일의 모든 코드를 C API 문법으로 되돌려야 합니다.
// 하지만 최신 FMOD는 C++ API 사용을 권장합니다.