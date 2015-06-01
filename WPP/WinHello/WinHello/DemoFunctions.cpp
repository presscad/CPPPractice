#include "DemoFunctions.h"
#include "SysMets.h"
#include <math.h>

#define NUM    1000
#define TWOPI  (2 * 3.14159)


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

void PaintRectangles(HWND hwnd,int cxClient,int cyClient)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint (hwnd, &ps) ;

	Rectangle (hdc,     cxClient / 8,     cyClient / 8,
		7 * cxClient / 8, 7 * cyClient / 8) ;

	MoveToEx  (hdc,        0,        0, NULL) ;
	LineTo    (hdc, cxClient, cyClient) ;

	MoveToEx  (hdc,        0, cyClient, NULL) ;
	LineTo    (hdc, cxClient,        0) ;

	Ellipse   (hdc,     cxClient / 8,     cyClient / 8,
		7 * cxClient / 8, 7 * cyClient / 8) ;

	RoundRect (hdc,     cxClient / 4,     cyClient / 4,
		3 * cxClient / 4, 3 * cyClient / 4,
		cxClient / 4,     cyClient / 4) ;

	EndPaint (hwnd, &ps) ;
}

void PaintPolygon(HWND hwnd,int iFillMode,POINT points[],int cxClient,int cyClient)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint (hwnd, &ps) ;
	int i;

	SelectObject (hdc, GetStockObject (GRAY_BRUSH)) ;

	for (i = 0 ; i < 10 ; i++)
	{
		points[i].x += cxClient / 2 ;
		points[i].y += cyClient / 4 ;
	}

	SetPolyFillMode (hdc, iFillMode) ;
	Polygon (hdc, points, 10) ;

	EndPaint (hwnd, &ps) ;
}

void DrawRectangle (HWND hwnd,int cxClient, int cyClient)
{
	HBRUSH hBrush ;
	HDC    hdc ;
	RECT   rect ;

	if (cxClient == 0 || cyClient == 0)
		return ;

	SetRect (&rect, rand () % cxClient, rand () % cyClient,
		rand () % cxClient, rand () % cyClient) ;

	hBrush = CreateSolidBrush (
		RGB (rand () % 256, rand () % 256, rand () % 256)) ;

	hdc = GetDC (hwnd) ;
	FillRect (hdc, &rect, hBrush) ;
	ReleaseDC (hwnd, hdc) ;
	DeleteObject (hBrush) ;
}

void PaintSinWave(HWND hwnd, int cxClient, int cyClient)
{
	int         i ;
	PAINTSTRUCT ps ;
	POINT       apt [NUM] ;
	HDC hdc = BeginPaint (hwnd, &ps) ;

	MoveToEx (hdc, 0,        cyClient / 2, NULL) ;
	LineTo   (hdc, cxClient, cyClient / 2) ;

	for (i = 0 ; i < NUM ; i++)
	{
		apt[i].x = i * cxClient / NUM ;
		apt[i].y = (int) (cyClient / 2 * (1 - sin (TWOPI * i / NUM))) ;
	}

	Polyline (hdc, apt, NUM) ;

	EndPaint (hwnd, &ps) ;
}

void DrawBezier (HDC hdc, POINT apt[])
{
	PolyBezier (hdc, apt, 4) ;

	MoveToEx (hdc, apt[0].x, apt[0].y, NULL) ;
	LineTo   (hdc, apt[1].x, apt[1].y) ;

	MoveToEx (hdc, apt[2].x, apt[2].y, NULL) ;
	LineTo   (hdc, apt[3].x, apt[3].y) ;
}

void CombieCloverRgn(HRGN &hRgnClip, int cxClient, int cyClient)
{
	HRGN        hRgnTemp[6] ;
	int i;
	HCURSOR hCursor = SetCursor (LoadCursor (NULL, IDC_WAIT)) ;
	ShowCursor (TRUE) ;

	if (hRgnClip)
		DeleteObject (hRgnClip) ;

	hRgnTemp[0] = CreateEllipticRgn (0, cyClient / 3,
		cxClient / 2, 2 * cyClient / 3) ;
	hRgnTemp[1] = CreateEllipticRgn (cxClient / 2, cyClient / 3,
		cxClient, 2 * cyClient / 3) ;
	hRgnTemp[2] = CreateEllipticRgn (cxClient / 3, 0,
		2 * cxClient / 3, cyClient / 2) ;
	hRgnTemp[3] = CreateEllipticRgn (cxClient / 3, cyClient / 2,
		2 * cxClient / 3, cyClient) ;
	hRgnTemp[4] = CreateRectRgn (0, 0, 1, 1) ;
	hRgnTemp[5] = CreateRectRgn (0, 0, 1, 1) ;
	hRgnClip    = CreateRectRgn (0, 0, 1, 1) ;

	CombineRgn (hRgnTemp[4], hRgnTemp[0], hRgnTemp[1], RGN_OR) ;
	CombineRgn (hRgnTemp[5], hRgnTemp[2], hRgnTemp[3], RGN_OR) ;
	CombineRgn (hRgnClip,    hRgnTemp[4], hRgnTemp[5], RGN_XOR) ;

	for (i = 0 ; i < 6 ; i++)
		DeleteObject (hRgnTemp[i]) ;

	SetCursor (hCursor) ;
	ShowCursor (FALSE) ;
}

void PaintClover(HWND hwnd,HRGN hRgnClip, int cxClient, int cyClient)
{
	double      fAngle, fRadius ;
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint (hwnd, &ps) ;

	SetViewportOrgEx (hdc, cxClient / 2, cyClient / 2, NULL) ;
	SelectClipRgn (hdc, hRgnClip) ;

	fRadius = _hypot (cxClient / 2.0, cyClient / 2.0) ;

	for (fAngle = 0.0 ; fAngle < TWOPI ; fAngle += TWOPI / 360)
	{
		MoveToEx (hdc, 0, 0, NULL) ;
		LineTo (hdc, (int) ( fRadius * cos (fAngle) + 0.5),
			(int) (-fRadius * sin (fAngle) + 0.5)) ;
	}
	EndPaint (hwnd, &ps) ;
}

void DrawBoxOutline(HWND hwnd, POINT ptBeg, POINT ptEnd)
{
	HDC hdc;

	hdc = GetDC(hwnd);

	SetROP2(hdc, R2_NOT);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, ptBeg.x, ptBeg.y, ptEnd.x, ptEnd.y);

	ReleaseDC(hwnd, hdc);
}

BOOL StringReverseW(PWSTR pWideCharStr, DWORD cchLength)
{
	PWSTR pEndOfStr = pWideCharStr + wcsnlen_s(pWideCharStr, cchLength) - 1;
	wchar_t cCharT;

	while (pWideCharStr < pEndOfStr)
	{
		cCharT = *pWideCharStr;
		*pWideCharStr = *pEndOfStr;
		*pEndOfStr = cCharT;

		pWideCharStr++;
		pEndOfStr--;
	}

	return(TRUE);
}

BOOL StringReverseA(PSTR pMultiByteStr, DWORD cchLength) {
	PWSTR pWideCharStr;
	int nLenOfWideCharStr;
	BOOL fOk = FALSE;

	// Calculate the number of characters needed to hold
	// the wide-character version of the string.
	nLenOfWideCharStr = MultiByteToWideChar(CP_ACP, 0,
		pMultiByteStr, cchLength, NULL, 0);

	// Allocate memory from the process' default heap to
	// accommodate the size of the wide-character string.
	// Don't forget that MultiByteToWideChar returns the
	// number of characters, not the number of bytes, so
	// you must multiply by the size of a wide character.
	pWideCharStr = (PWSTR)HeapAlloc(GetProcessHeap(), 0,
		nLenOfWideCharStr * sizeof(wchar_t));

	if (pWideCharStr == NULL)
		return(fOk);

	// Convert the multibyte string to a wide-character string.
	MultiByteToWideChar(CP_ACP, 0, pMultiByteStr, cchLength,
		pWideCharStr, nLenOfWideCharStr);

	// Call the wide-character version of this
	// function to do the actual work.
	fOk = StringReverseW(pWideCharStr, cchLength);

	if (fOk) {
		// Convert the wide-character string back
		// to a multibyte string.
		WideCharToMultiByte(CP_ACP, 0, pWideCharStr, cchLength,
			pMultiByteStr, (int)strlen(pMultiByteStr), NULL, NULL);
	}

	// Free the memory containing the wide-character string.
	HeapFree(GetProcessHeap(), 0, pWideCharStr);

	return(fOk);
}

