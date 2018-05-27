#include <Windows.h>
#include "stdafx.h"
#include "figures.h"
#define ID_BUTTON_QUEEN 200
#define ID_BUTTON_KNIGHT 201
#define ID_BUTTON_ROOK 202
#define ID_BUTTON_BISHOP 203

board _board;

HWND MDIchoose;
HWND choose;
HWND Mainwnd;
HINSTANCE hinstance;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK chooseproc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR szCmdLine, int iCmdShow)
{
	hinstance = hInst;
	MSG msg;
	if (!regwinclass(L"bmpapp", WndProc, hInst))
	{
		MessageBox(NULL, L"Ошибка создания класса окна", L"Ошибка", MB_OK);
		return 0;
	}
	if (!regwinclass(L"choose", chooseproc, hInst))
	{
		MessageBox(NULL, L"Ошибка создания класса окна", L"Ошибка", MB_OK);
		return 0;
	}

	Mainwnd = CreateWindow(L"bmpapp", L"Bmptest", WS_DLGFRAME | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 776, 799, NULL, NULL, hInst, NULL);
	
	if (!Mainwnd)
	{
		MessageBox(NULL, L"Ошибка создания окна", L"Ошибка", MB_OK);
		return 0;
	}

	ShowWindow(Mainwnd, iCmdShow);
	UpdateWindow(Mainwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(MDIchoose, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM Wparam, LPARAM Lparam)
{
	static PAINTSTRUCT  ps;
	static HDC hdc;
	RECT rect;
	static set<pos, comp> clres;
	static figure * current = NULL;
	switch (imsg)
	{
	case WM_CREATE:
	{
		CLIENTCREATESTRUCT ccs;
		memset(&ccs, 0, sizeof(CLIENTCREATESTRUCT));
		MDIchoose = CreateWindow(L"MDICLIENT", L"" ,WS_CHILD, 0, 0, 0, 0, hwnd, NULL, hinstance, (LPSTR)&ccs);
		ShowWindow(MDIchoose, SW_HIDE);
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		_board.draw(hdc, hwnd);
		if (current)
			_board.to_colour(hdc, hwnd, clres);
		EndPaint(hwnd, &ps);
		break;
	}
	case ID_BUTTON_QUEEN:
	{
		ShowWindow(MDIchoose, SW_HIDE);
		_board.transform(current, 0);
		current = NULL;
		if (_board.is_check())
		{
			if (_board.is_mate())
			{
				MessageBox(NULL, L"Мат", L"", MB_OK);
				_board.place();
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, false);
				break;
			}
			MessageBox(NULL, L"Шах", L"", MB_OK);
		}
		break;
	}
	case ID_BUTTON_ROOK:
	{
		ShowWindow(MDIchoose, SW_HIDE);
		_board.transform(current, 1);
		current = NULL;
		if (_board.is_check())
		{
			if (_board.is_mate())
			{
				MessageBox(NULL, L"Мат", L"", MB_OK);
				_board.place();
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, false);
				break;
			}
			MessageBox(NULL, L"Шах", L"", MB_OK);
		}
		break;
	}
	case ID_BUTTON_KNIGHT:
	{
		ShowWindow(MDIchoose, SW_HIDE);
		_board.transform(current, 2);
		current = NULL;
		if (_board.is_check())
		{
			if (_board.is_mate())
			{
				MessageBox(NULL, L"Мат", L"", MB_OK);
				_board.place();
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, false);
				break;
			}
			MessageBox(NULL, L"Шах", L"", MB_OK);
		}
		break;
	}
	case ID_BUTTON_BISHOP:
	{
		ShowWindow(MDIchoose, SW_HIDE);
		_board.transform(current, 3);
		current = NULL;
		if (_board.is_check())
		{
			if (_board.is_mate())
			{
				MessageBox(NULL, L"Мат", L"", MB_OK);
				_board.place();
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, false);
				break;
			}
			MessageBox(NULL, L"Шах", L"", MB_OK);
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		UINT xpos = (LOWORD(Lparam) - 20) / 90;
		UINT ypos = (HIWORD(Lparam) - 20) / 90;
		if ((xpos > 7) || (ypos > 7))
			break;
		if ((dynamic_cast<rook*>(current)) && (clres.is_in(pos(xpos, ypos))))
			dynamic_cast<rook*>(current)->is_moved = true;
		if ((dynamic_cast<king*>(current)) && (clres.is_in(pos(xpos, ypos))))
		{
			dynamic_cast<king*>(current)->is_moved = true;
			if (pos(xpos - 2, ypos) == *current)
			{
				_board.Castling(true);
				current = NULL;
				clres = set<pos, comp>();
				_board.change_turn();
				if (_board.is_check())
				{
					if (_board.is_mate())
					{
						MessageBox(NULL, L"Мат", L"", MB_OK);
						_board.place();
						GetClientRect(hwnd, &rect);
						InvalidateRect(hwnd, &rect, false);
						break;
					}
					MessageBox(NULL, L"Шах", L"", MB_OK);
				}
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, false);
				break;
			}
			if (pos(xpos + 2, ypos) == *current)
			{
				_board.Castling(false);
				current = NULL;
				clres = set<pos, comp>();
				_board.change_turn();
				if (_board.is_check())
				{
					if (_board.is_mate())
					{
						MessageBox(NULL, L"Мат", L"", MB_OK);
						_board.place();
						GetClientRect(hwnd, &rect);
						InvalidateRect(hwnd, &rect, false);
						break;
					}
					MessageBox(NULL, L"Шах", L"", MB_OK);
				}
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, false);
				break;
			}
		}
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
			if (dynamic_cast<pawn*>(current)->is_on_last_line())
			{
				MSG mymsg;


				choose = CreateMDIWindow(L"choose", L"", WS_DLGFRAME | WS_MAXIMIZE, CW_USEDEFAULT, CW_USEDEFAULT, 776, 799, MDIchoose, hinstance, NULL);
				ShowWindow(MDIchoose, SW_SHOW);
				ShowWindow(choose, SW_SHOW);
				//ShowWindow(MDIchoose, SW_HIDE);
			}
			else
				current = NULL;
			clres = set<pos, comp>();

			_board.change_turn();
			if (_board.is_check())
			{
				if (_board.is_mate())
				{
					MessageBox(NULL, L"Мат", L"", MB_OK);
					_board.place();
					GetClientRect(hwnd, &rect);
					InvalidateRect(hwnd, &rect, false);
					break;
				}
				MessageBox(NULL, L"Шах", L"", MB_OK);
			}
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, false);
			break;
		}
		if ((current) && (clres.is_in(pos(xpos, ypos))))
		{
			if (_board.is_figure(xpos, ypos))
				_board.get_figure(xpos, ypos)->remove();
			current->fset(xpos, ypos);
			current = NULL;
			clres = set<pos, comp>();
			_board.change_turn();
			if (_board.is_check())
			{
				if (_board.is_mate())
				{
					MessageBox(NULL, L"Мат", L"", MB_OK);
					_board.place();
					GetClientRect(hwnd, &rect);
					InvalidateRect(hwnd, &rect, false);
					break;
				}
				MessageBox(NULL, L"Шах", L"", MB_OK);
			}
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, false);
			break;
		}
		clres = _board.click(xpos, ypos);
		if (!clres.is_empty())
		{
			current = _board.get_figure(xpos, ypos);
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, false);
		}
		else
		{
			current = NULL;
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, false);
		}
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefFrameProcW(hwnd, MDIchoose, imsg, Wparam, Lparam);
}


LRESULT CALLBACK chooseproc(HWND hwnd, UINT imsg, WPARAM Wparam, LPARAM Lparam)
{
	switch (imsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		TextOutW(hdc, 10, 10, L"Выберете фигуру", 15);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_CREATE:
	{
		CreateWindow(L"button", L"Ферзь", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 30, 60, 20, hwnd, (HMENU)ID_BUTTON_QUEEN, NULL, NULL);
		CreateWindow(L"button", L"Ладья", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 70, 60, 20, hwnd, (HMENU)ID_BUTTON_ROOK, NULL, NULL);
		CreateWindow(L"button", L"Конь", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 80, 30, 60, 20, hwnd, (HMENU)ID_BUTTON_KNIGHT, NULL, NULL);
		CreateWindow(L"button", L"Слон", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 80, 70, 60, 20, hwnd, (HMENU)ID_BUTTON_BISHOP, NULL, NULL);
		return 0;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(Wparam))
		{
		case ID_BUTTON_QUEEN:
		{
			SendMessage(Mainwnd, ID_BUTTON_QUEEN, Wparam, Lparam);
			return 0;
		}
		case ID_BUTTON_ROOK:
		{
			SendMessage(Mainwnd, ID_BUTTON_ROOK, Wparam, Lparam);
			return 0;
		}
		case ID_BUTTON_KNIGHT:
		{
			SendMessage(Mainwnd, ID_BUTTON_KNIGHT, Wparam, Lparam);
			return 0;
		}
		case ID_BUTTON_BISHOP:
		{
			SendMessage(Mainwnd, ID_BUTTON_BISHOP, Wparam, Lparam);
			return 0;
		}
		}
	}
	}
	return DefMDIChildProc(hwnd, imsg, Wparam, Lparam);
}