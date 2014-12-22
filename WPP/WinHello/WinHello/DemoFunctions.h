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
void PaintRectangles(HWND hwnd,int cxClient,int cyClient);
void PaintPolygon(HWND hwnd,int iFillMode,POINT points[],int cxClient,int cyClient);
void DrawRectangle(HWND hwnd,int cxClient, int cyClient);
void PaintSinWave(HWND hwnd, int cxClient, int cyClient);
void DrawBezier (HDC hdc, POINT apt[]);
void CombieCloverRgn(HRGN &hRgnClip, int cxClient, int cyClient);
void PaintClover(HWND hwnd,HRGN hRgnClip, int cxClient, int cyClient);
void DrawBoxOutline(HWND hwnd, POINT ptBeg, POINT ptEnd);
#endif
