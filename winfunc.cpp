#include <windows.h>
#include "stdafx.h"
bool regwinclass(TCHAR * appname, LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM), HINSTANCE hinst)
{
	WNDCLASSEX  wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hinst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(0);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = appname;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wndclass);
}

void bmppaint(HWND hwnd, HDC hdc, TCHAR * Filename, UINT x, UINT y, UINT cx, UINT cy)
{
	HDC          hCompatibleDC;
	HANDLE       hBitmap, hOldBitmap;
	BITMAP Bitmap;
	hBitmap = LoadImage(NULL, Filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBitmap)
	{
		MessageBox(NULL, L"File not found!", L"Error", MB_OK);
		exit(3);
	}
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
	hCompatibleDC = CreateCompatibleDC(hdc);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	BitBlt(hdc, x, y, cx, cy, hCompatibleDC, 0, 0, SRCCOPY);
	DeleteDC(hCompatibleDC);
}