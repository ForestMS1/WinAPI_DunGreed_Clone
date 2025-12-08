#include "pch.h"
#include "CSoundMgr.h"
#include <io.h>
#include <filesystem>

CSoundMgr* CSoundMgr::m_pInstance = nullptr;

CSoundMgr::CSoundMgr()
{
    m_pSystem = nullptr;
    ZeroMemory(m_pChannelArr, sizeof(m_pChannelArr));
}

CSoundMgr::~CSoundMgr()
{
    Release();
}

void CSoundMgr::Initialize()
{
    FMOD_RESULT res;

    res = FMOD_System_Create(&m_pSystem);
    if (res != FMOD_OK)
    {
        printf("FMOD_System_Create FAILED : %d\n", res);
        return;
    }

    res = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, nullptr);
    if (res != FMOD_OK)
    {
        printf("FMOD_System_Init FAILED : %d\n", res);
        return;
    }

    LoadSoundFile();
}

void CSoundMgr::Release()
{
    for (auto& elem : m_mapSound)
        FMOD_Sound_Release(elem.second);

    m_mapSound.clear();

    if (m_pSystem)
    {
        FMOD_System_Close(m_pSystem);
        FMOD_System_Release(m_pSystem);
    }
}

void CSoundMgr::PlaySound(const wchar_t* pSoundKey, CHANNELID eID, float fVolume)
{
    auto iter = m_mapSound.find(pSoundKey);
    if (iter == m_mapSound.end())
        return;

    FMOD_System_PlaySound(
        m_pSystem,
        FMOD_CHANNEL_FREE,
        iter->second,
        FALSE,
        &m_pChannelArr[eID]
    );

    FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);
    FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(const wchar_t* pSoundKey, float fVolume)
{
    auto iter = m_mapSound.find(pSoundKey);
    if (iter == m_mapSound.end())
        return;

    FMOD_System_PlaySound(
        m_pSystem,
        FMOD_CHANNEL_FREE,
        iter->second,
        FALSE,
        &m_pChannelArr[SOUND_BGM]
    );

    FMOD_Channel_SetMode(m_pChannelArr[SOUND_BGM], FMOD_LOOP_NORMAL);
    FMOD_Channel_SetVolume(m_pChannelArr[SOUND_BGM], fVolume);

    FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopSound(CHANNELID eID)
{
    if (m_pChannelArr[eID])
        FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundMgr::StopAll()
{
    for (int i = 0; i < MAXCHANNEL; ++i)
        if (m_pChannelArr[i])
            FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
{
    if (m_pChannelArr[eID])
        FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

    FMOD_System_Update(m_pSystem);
}

void CSoundMgr::LoadSoundFile()
{
    _finddata_t fd;
    intptr_t handle = _findfirst("../Resources/Sounds/*.*", &fd);

    if (handle == -1)
        return;

    do
    {
        char fullPath[260];
        sprintf_s(fullPath, "../Resources/Sounds/%s", fd.name);

        FMOD_SOUND* pSound = nullptr;

        FMOD_RESULT res = FMOD_System_CreateSound(
            m_pSystem,
            fullPath,
            FMOD_DEFAULT,
            0,
            &pSound
        );

        if (res == FMOD_OK)
        {
            int wlen = MultiByteToWideChar(CP_ACP, 0, fd.name, -1, nullptr, 0);
            std::wstring key(wlen, 0);

            MultiByteToWideChar(CP_ACP, 0, fd.name, -1, &key[0], wlen);

            if (!key.empty() && key.back() == L'\0')
                key.pop_back();

            m_mapSound.insert({ key, pSound });
        }

    } while (_findnext(handle, &fd) != -1);

    _findclose(handle);
}