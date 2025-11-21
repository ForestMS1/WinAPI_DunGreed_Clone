#pragma once
#define WINCX 800
#define WINCY 600

#define PURE = 0

#define PI 3.14592f


typedef struct tagInfo
{
	float fX, fY; // 중심좌표
	float fCX, fCY; // 가로 세로 길이
}INFO;


extern HWND g_hWnd;