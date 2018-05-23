#include <Windows.h>
#include "stdafx.h"
#include "figures.h"
board _board;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR szCmdLine, int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	if (!regwinclass(L"bmpapp", WndProc, hInst))
	{
		MessageBox(NULL, L"������ �������� ������ ����", L"������", MB_OK);
		return 0;
	}

	hwnd = CreateWindow(L"bmpapp", L"Bmptest", WS_DLGFRAME | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 776, 799, NULL, NULL, hInst, NULL);
	
	if (!hwnd)
	{
		MessageBox(NULL, L"������ �������� ����", L"������", MB_OK);
		return 0;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM Wparam, LPARAM Lparam)
{
	static PAINTSTRUCT  ps;
	static HDC hdc;
	static set<pos, comp> clres;
	static figure * current = NULL;
	switch (imsg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		_board.draw(hdc, hwnd);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		_board.draw(hdc, hwnd);
		UINT xpos = (LOWORD(Lparam) - 20) / 90;
		UINT ypos = (HIWORD(Lparam) - 20) / 90;
		if ((xpos > 7) || (ypos > 7))
			break;
		if ((dynamic_cast<pawn*>(current)) && (clres.is_in(pos(xpos, ypos))))
		{
			if ((!_board.is_figure(xpos, ypos)) && ((pos(xpos - 1,ypos + 1) == *current) || (pos(xpos + 1, ypos + 1) == *current)))
				_board.get_figure(xpos, ypos + 1)->remove();
			if (_board.is_figure(xpos, ypos))
				_board.get_figure(xpos, ypos)->remove();
			current->fset(xpos, ypos);
			if (dynamic_cast<pawn*>(current)->cond == 0)
			{
				dynamic_cast<pawn*>(current)->cond = 1;
			}
			//todo ����������� �����������
			current = NULL;
			clres = set<pos, comp>();

			//if (_board.is_white_turn)
			//	_board.blackcheck = _board.is_blackcheck();
			//else
			//	_board.whitecheck = _board.is_whitecheck();
			_board.invert();
			_board.draw(hdc, hwnd);
			break;
		}
		if ((current) && (clres.is_in(pos(xpos, ypos))))
		{
			if (_board.is_figure(xpos, ypos))
				_board.get_figure(xpos, ypos)->remove();
			current->fset(xpos, ypos);
			current = NULL;
			clres = set<pos, comp>();
			_board.invert();
			_board.draw(hdc, hwnd);
			break;
		}
		clres = _board.click(xpos, ypos);
		if (!clres.is_empty())
		{
			_board.to_colour(hdc, hwnd, clres);
			current = _board.get_figure(xpos, ypos);
		}
		break;
	}
	case WM_DESTROY:
	{
		EndPaint(hwnd, &ps);
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd, imsg, Wparam, Lparam);
}