#include "pch.h"
#include "CFontMgr.h"

CFontMgr* CFontMgr::m_pInstance = nullptr;

// 생성자
CFontMgr::CFontMgr() : m_baseLogFont({}) {}

// 소멸자 (Cleanup을 호출하여 반드시 리소스를 해제합니다)
CFontMgr::~CFontMgr() {
    Cleanup();
}

// ====================================================================
// 1. 초기화 메서드
// ====================================================================

bool CFontMgr::Initialize(const std::wstring& filePath, const std::wstring& facename, int initialSize) {
    if (!m_fontCache.empty()) {
        // 이미 초기화된 경우
        return false;
    }

    m_fontFilePath = filePath;
    m_fontFacename = facename;

    // 1. 폰트 리소스 로드 (시스템 등록)
    if (AddFontResourceEx(m_fontFilePath.c_str(), FR_PRIVATE, 0) == 0) {
        // 폰트 파일 로드 실패
        return false;
    }

    // 2. 기본 HFONT를 생성하고 속성(LOGFONT)을 추출하여 저장합니다.
    // 이 폰트는 캐시에도 등록됩니다.
    HFONT hInitialFont = CreateFont(
        -initialSize, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        m_fontFacename.c_str()
    );

    if (hInitialFont == NULL) {
        // HFONT 생성 실패 시 등록된 리소스 해제
        RemoveFontResourceEx(m_fontFilePath.c_str(), FR_PRIVATE, 0);
        return false;
    }

    // 기본 속성 저장 및 캐시 등록
    GetObject(hInitialFont, sizeof(LOGFONT), &m_baseLogFont);
    m_fontCache[initialSize] = hInitialFont;

    return true;
}

// ====================================================================
// 내부 헬퍼 메서드: 폰트 핸들을 가져오거나 생성
// ====================================================================

HFONT CFontMgr::GetOrCreateFont(int size) {
    // 1. 캐시에 해당 크기의 폰트가 있는지 확인
    if (m_fontCache.count(size)) {
        return m_fontCache[size];
    }

    // 2. 기본 LOGFONT를 복사하고 높이(크기)만 변경합니다.
    LOGFONT lf = m_baseLogFont;
    lf.lfHeight = -size; // 음수 사용으로 픽셀 높이 지정

    // 3. 새로운 HFONT 생성
    HFONT hNewFont = CreateFontIndirect(&lf);

    // 4. 생성 성공 시 맵에 저장 후 반환
    if (hNewFont) {
        m_fontCache[size] = hNewFont;
    }
    return hNewFont;
}


// ====================================================================
// 2. 텍스트 출력 메서드
// ====================================================================

void CFontMgr::DrawText(HDC hdc, int x, int y, const std::wstring& text, int size, COLORREF color) {
    // 1. 원하는 크기의 폰트 핸들을 얻어옵니다. (없으면 자동으로 생성)
    HFONT hFont = GetOrCreateFont(size);

    if (hFont) {
        // 2. 기존 폰트 저장 후, 원하는 크기의 폰트 선택
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

        // 3. 텍스트 설정
        SetTextColor(hdc, color);
        SetBkMode(hdc, TRANSPARENT);

        // 4. 텍스트 출력
        TextOut(hdc, x, y, text.c_str(), (int)text.length());

        // 5. 원래 폰트 복원
        SelectObject(hdc, hOldFont);
    }
}

// ====================================================================
// 3. 정리 메서드
// ====================================================================

void CFontMgr::Cleanup() {
    // 1. 맵에 저장된 모든 HFONT 핸들 삭제
    for (auto const& pair : m_fontCache) {
        DeleteObject(pair.second);
    }
    m_fontCache.clear();

    // 2. 폰트 리소스 제거
    if (!m_fontFilePath.empty()) {
        RemoveFontResourceEx(m_fontFilePath.c_str(), FR_PRIVATE, 0);
        m_fontFilePath.clear();
    }
}