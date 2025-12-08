#pragma once

#include "Define.h"
#include <map>
#include <string>
#include <fmod.h>

class CSoundMgr
{
public:
    static CSoundMgr* Get_Instance()
    {
        if (nullptr == m_pInstance)
            m_pInstance = new CSoundMgr;
        return m_pInstance;
    }
    static void Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    CSoundMgr();
    ~CSoundMgr();

public:
    void Initialize();
    void Release();

public:
    void PlaySound(const wchar_t* pSoundKey, CHANNELID eID, float fVolume);
    void PlayBGM(const wchar_t* pSoundKey, float fVolume);
    void StopSound(CHANNELID eID);
    void StopAll();
    void SetChannelVolume(CHANNELID eID, float fVolume);

private:
    void LoadSoundFile();

private:
    static CSoundMgr* m_pInstance;

    std::map<std::wstring, FMOD_SOUND*> m_mapSound;
    FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
    FMOD_SYSTEM* m_pSystem;
};