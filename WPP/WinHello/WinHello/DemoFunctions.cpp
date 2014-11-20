#include "DemoFunctions.h"
#include "SysMets.h"


int CDECL MessageBoxPrintf(TCHAR* szCaption, TCHAR* szFormat, ...)
{
	TCHAR szBuffer[1024];
	va_list pArgList;

	va_start(pArgList,szFormat);

	_vsntprintf_s(szBuffer, sizeof(szBuffer) / sizeof(TCHAR),
		szFormat, pArgList);

	va_end(pArgList);

	return MessageBox(NULL,szBuffer,szCaption,0);
}

void ShowScreenSize()
{
	int cxScreen, cyScreen;
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);

	MessageBoxPrintf(TEXT("Screen Size"),
		TEXT("The screen is %i pixels wide by %i pixels high."),
		cxScreen,
		cyScreen);

	PlaySound(TEXT("hellowin.wav"),NULL,SND_FILENAME | SND_ASYNC);
}

void GetTextSize( HWND hwnd, int& cxChar,int& cxCaps,int& cyChar )
{
	TEXTMETRIC tm;
	HDC hdc = GetDC(hwnd);
	GetTextMetrics(hdc,&tm);
	cxChar = tm.tmAveCharWidth;
	cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2)*cxChar/2;
	cyChar = tm.tmHeight + tm.tmExternalLeading;
	ReleaseDC(hwnd,hdc);
}

void SetWinScrollInfo( HWND hwnd,UINT iMask,int iMin,int iMax,UINT iPage,int iType,BOOL redraw )
{
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = iMask;
	si.nMin = iMin;
	si.nMax = iMax;
	si.nPage = iPage;
	SetScrollInfo(hwnd,iType,&si,redraw);
}

void DealWithScrollMsg( HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam,int iUnit,int iType )
{
	// Get all the vertical scroll bar information
	SCROLLINFO si;
	int iPos = 0;
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	GetScrollInfo(hwnd,iType,&si);

	// Save the position for comparison later on
	iPos = si.nPos;

	if(iType == SB_VERT)
	{
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
	}
	else if(iType == SB_HORZ)
	{
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

	}

	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	SetScrollInfo(hwnd,iType,&si,TRUE);
	GetScrollInfo(hwnd,iType,&si);

	// If the position has changed, scroll the window and update it
	if(si.nPos != iPos)
	{
		ScrollWindow(hwnd,0,iUnit * (iPos - si.nPos),NULL,NULL);
		UpdateWindow(hwnd);
	}
}

void PrintText( HWND hwnd,int cxChar,int cyChar,int cxCaps )
{
	HDC hdc;
	PAINTSTRUCT ps;
	SCROLLINFO si;
	int iVertPos,iHorzPos,iPaintBeg,iPaintEnd;
	int x,y;
	TCHAR szBuffer[10];

	hdc = BeginPaint(hwnd,&ps);

	si.cbSize = sizeof(si);
	si.fMask = SIF_POS;
	GetScrollInfo(hwnd,SB_VERT,&si);
	iVertPos = si.nPos;

	GetScrollInfo(hwnd,SB_HORZ,&si);
	iHorzPos = si.nPos;

	iPaintBeg = max(0,iVertPos + ps.rcPaint.top / cyChar);
	iPaintEnd = min(NUMLINES - 1, iVertPos + ps.rcPaint.bottom / cyChar);

	for (int i = iPaintBeg ; i <= iPaintEnd ; i++)
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
}