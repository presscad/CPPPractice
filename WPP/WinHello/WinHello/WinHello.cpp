#include <Windows.h>
#include <tchar.h>
#include "sysmets.h"

int CDECL MessageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat, ...)
{
	TCHAR szBuffer[1024];
	va_list pArgList;

	va_start(pArgList,szFormat);

	_vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR),
		        szFormat, pArgList);

	va_end(pArgList);

	return MessageBox(NULL,szBuffer,szCaption,0);
}

LRESULT CALLBACK WndProc( HWND,UINT,WPARAM,LPARAM);

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 PSTR szCmdLine, int iCmdShow )
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("This program requires Windows NT!"),szAppName,MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szAppName,
		TEXT("The Hello Program"),
		WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	static int  cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth ;
	HDC hdc;
	int         i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd ;
	PAINTSTRUCT ps;
	SCROLLINFO si;
	TCHAR szBuffer[10];
	TEXTMETRIC tm;

	RECT rect;

	switch (message)
	{
	case WM_CREATE:

		/*
		int cxScreen, cyScreen;
		cxScreen = GetSystemMetrics(SM_CXSCREEN);
		cyScreen = GetSystemMetrics(SM_CYSCREEN);

		MessageBoxPrintf(TEXT("Screen Size"),
						 TEXT("The screen is %i pixels wide by %i pixels high."),
						 cxScreen,
						 cyScreen);

		PlaySound(TEXT("hellowin.wav"),NULL,SND_FILENAME | SND_ASYNC);
		*/

		hdc = GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2)*cxChar/2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hwnd,hdc);

		iMaxWidth = 40 * cxChar + 22 * cxCaps;

		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = NUMLINES - 1;
		si.nPage = cyClient / cyChar;
		SetScrollInfo(hwnd,SB_VERT,&si,TRUE);

		si.cbSize = sizeof(si);
		si.fMask = SIF_PAGE | SIF_PAGE;
		si.nMin = 0 ;
		si.nMax = 2 + iMaxWidth / cxChar;
		si.nPage = cxClient / cxChar;
		SetScrollInfo(hwnd,SB_HORZ,&si,TRUE);

		return 0;

	case WM_VSCROLL:

		// Get all the vertical scroll bar information
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd,SB_VERT,&si);

		// Save the position for comparison later on
		iVertPos = si.nPos;

		switch(LOWORD(wParam))
		{
		case SB_TOP:
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;

		case SB_LINEUP:
			si.nPos -= 1;
			break;

		case SB_LINEDOWN:
			si.nPos += 1;
			break;

		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;

		}

		// Set the position and then retrieve it.  Due to adjustments
		//   by Windows it may not be the same as the value set.
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd,SB_VERT,&si,TRUE);
		GetScrollInfo(hwnd,SB_VERT,&si);

		// If the position has changed, scroll the window and update it
		if(si.nPos != iVertPos)
		{
			ScrollWindow(hwnd,0,cyChar * (iVertPos - si.nPos),NULL,NULL);
			UpdateWindow(hwnd);
		}

		return 0;

	case WM_HSCROLL:
		

		si.cbSize = sizeof (si) ;
		si.fMask  = SIF_ALL ;

		// Save the position for comparison later on

		GetScrollInfo (hwnd, SB_HORZ, &si) ;
		iHorzPos = si.nPos ;

		switch (LOWORD (wParam))
		{
		case SB_LINELEFT:
			si.nPos -= 1 ;
			break ;

		case SB_LINERIGHT:
			si.nPos += 1 ;
			break ;

		case SB_PAGELEFT:
			si.nPos -= si.nPage ;
			break ;

		case SB_PAGERIGHT:
			si.nPos += si.nPage ;
			break ;

		case SB_THUMBPOSITION:
			si.nPos = si.nTrackPos ;
			break ;

		default :
			break ;
		}
		// Set the position and then retrieve it.  Due to adjustments
		//   by Windows it may not be the same as the value set.

		si.fMask = SIF_POS ;
		SetScrollInfo (hwnd, SB_HORZ, &si, TRUE) ;
		GetScrollInfo (hwnd, SB_HORZ, &si) ;

		// If the position has changed, scroll the window 

		if (si.nPos != iHorzPos)
		{
			ScrollWindow (hwnd, cxChar * (iHorzPos - si.nPos), 0, 
				NULL, NULL) ;
		}
		return 0 ;

	case  WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		//GetClientRect(hwnd,&rect);
		//DrawText(hdc,TEXT("Hello Windows 7!"),-1,&rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		GetScrollInfo(hwnd,SB_VERT,&si);
		iVertPos = si.nPos;

		GetScrollInfo(hwnd,SB_HORZ,&si);
		iHorzPos = si.nPos;

		iPaintBeg = max(0,iVertPos + ps.rcPaint.top / cyChar);
		iPaintEnd = min(NUMLINES - 1, iVertPos + ps.rcPaint.bottom / cyChar);

		for (i = iPaintBeg ; i <= iPaintEnd ; i++)
		{
			x = cxChar * (1 - iHorzPos) ;
			y = cyChar * (i - iVertPos) ;

			TextOut (hdc, x, y,sysmetrics[i].szLabel,
				lstrlen (sysmetrics[i].szLabel)) ;

			TextOut (hdc, x + 22 * cxCaps, y,sysmetrics[i].szDesc,
				lstrlen (sysmetrics[i].szDesc)) ;

			SetTextAlign (hdc, TA_RIGHT | TA_TOP) ;

			TextOut (hdc, x + 22 * cxCaps + 40 * cxChar, y, szBuffer,
				wsprintf (szBuffer, TEXT ("%5d"),
				GetSystemMetrics (sysmetrics[i].iIndex))) ;

			SetTextAlign (hdc, TA_LEFT | TA_TOP) ;
		}

		EndPaint(hwnd,&ps);
		return 0 ;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0 ;
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
}