#pragma once
//file to linc functions
bool regwinclass(TCHAR * appname, LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM), HINSTANCE hinst);
void bmppaint(HWND hwnd, HDC hdc, TCHAR * Filename, UINT x, UINT y, UINT cx, UINT cy);