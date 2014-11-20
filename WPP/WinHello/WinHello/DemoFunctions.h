#ifndef DEMOFUNCTION_H
#define DEMOFUNCTION_H

#include <Windows.h>
#include <tchar.h>

int CDECL MessageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat, ...);
void ShowScreenSize();
void GetTextSize(HWND hwnd,int& cxChar,int& cxCaps,int& cyChar);
void SetWinScrollInfo(HWND hwnd,UINT iMask,int iMin,int iMax,UINT iPage,int iType,BOOL redraw);
void DealWithScrollMsg(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam,int iUnit,int iType);
void PrintText(HWND hwnd,int cxChar,int cyChar,int cxCaps);
#endif
