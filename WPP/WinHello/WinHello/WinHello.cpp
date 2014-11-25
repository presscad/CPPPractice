#include "DemoFunctions.h"

#include <math.h>

#define TWO_PI (2.0 * 3.14159)


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



LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HRGN hRgnClip ;
	static int  cxClient, cyClient ;
	double      fAngle, fRadius ;
	HCURSOR     hCursor ;
	HDC         hdc ;
	HRGN        hRgnTemp[6] ;
	int         i ;
	PAINTSTRUCT ps ;

	switch (iMsg)
	{
	case WM_SIZE:
		cxClient = LOWORD (lParam) ;
		cyClient = HIWORD (lParam) ;

		CombieCloverRgn(hRgnClip,cxClient,cyClient);
		
		return 0 ;

	case WM_PAINT:
		
		PaintClover(hwnd,hRgnClip,cxClient,cyClient);

		return 0 ;

	case WM_DESTROY:
		DeleteObject (hRgnClip) ;
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
}