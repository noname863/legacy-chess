#pragma once
#include "figures.h"
#include "stdafx.h"
board::board()
{
	is_white_turn = true;
	count = 0;
	delete[] a;
	a = new figure*[32];
	a[0] = new rook;
	a[1] = new rook;
	a[2] = new knight;
	a[3] = new knight;
	a[4] = new bishop;
	a[5] = new bishop;
	a[6] = new queen;
	a[7] = new king;
	for (size_t i = 8; i < 16; i++)
		a[i] = new pawn;
	a[16] = new rook;
	a[17] = new rook;
	a[18] = new knight;
	a[19] = new knight;
	a[20] = new bishop;
	a[21] = new bishop;
	a[22] = new queen;
	a[23] = new king;
	for (size_t i = 24; i < 32; i++)
		a[i] = new pawn;
	place();
}


board::~board()
{
	delete[] a;
}


bool board::is_figure(unsigned char x, unsigned char y)
{
	for (size_t i = 0; i < 32; i++)
		if ((a[i]->x == x) && (a[i]->y == y))
			return true;
	return false;
}

void board::draw(HDC hdc, HWND hwnd)
{
	size_t i = 0;
	if (is_white_turn)
		bmppaint(hwnd, hdc, L"desk.bmp", 0, 0, 760, 760);
	else
		bmppaint(hwnd, hdc, L"Rdesk.bmp", 0, 0, 760, 760);
	for (; i < 2; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"WRookB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"WRookW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	for (; i < 4; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"WKnightB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"WKnightW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	for (; i < 6; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"WBishopB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"WBishopW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	if (!a[i]->is_remove())
		if ((a[i]->x + a[i]->y) % 2)
			bmppaint(hwnd, hdc, L"WQueenB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"WQueenW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	i++;
	if (!a[i]->is_remove())
		if ((a[i]->x + a[i]->y) % 2)
			bmppaint(hwnd, hdc, L"WKingB.bmp", 20 + a[i]->x * 90 , 20 + a[i]->y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"WKingW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	i++;
	for (; i < 16; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"WPawnB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"WPawnW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	for (; i < 18; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"BRookB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"BRookW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	for (; i < 20; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"BKnightB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"BKnightW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	for (; i < 22; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"BBishopB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"BBishopW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	if (!a[i]->is_remove())
		if ((a[i]->x + a[i]->y) % 2)
			bmppaint(hwnd, hdc, L"BQueenB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"BQueenW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	i++;
	if (!a[i]->is_remove())
		if ((a[i]->x + a[i]->y) % 2)
			bmppaint(hwnd, hdc, L"BKingB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"BKingW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
	i++;
	for (; i < 32; i++)
		if (!a[i]->is_remove())
			if ((a[i]->x + a[i]->y) % 2)
				bmppaint(hwnd, hdc, L"BPawnB.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"BPawnW.bmp", 20 + a[i]->x * 90, 20 + a[i]->y * 90, 90, 90);
}

void board::to_colour(HDC hdc, HWND hwnd, set<pos, comp> &t)
{
	set<pos, comp>::iterator it = t.begin();
	size_t i;
	for (; it != t.end(); ++it)
	{
		i = 0;
		for (; i < 32; i++)
			if (*a[i] == *it)
				break;
		if (i == 32)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"Gblack.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"Gwhite.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 2)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GWRookB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GWRookW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 4)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GWKnightB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GWKnightW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 6)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GWBishopB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GWBishopW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 7)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GWQueenB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GWQueenW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 8)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GWKingB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GWKingW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 16)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GWPawnB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GWPawnW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 18)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GBRookB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GBRookW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 20)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GBKnightB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GBKnightW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 22)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GBBishopB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GBBishopW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 23)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GBQueenB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GBQueenW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 24)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GBKingB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GBKingW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
		if (i < 32)
		{
			if (((*it).x + (*it).y) % 2)
				bmppaint(hwnd, hdc, L"GBPawnB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			else
				bmppaint(hwnd, hdc, L"GBPawnW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
			continue;
		}
	}
	i = 0;
	for (; i < 32; i++)
		if (*a[i] == *it)
			break;
	if (i == 32)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"Gblack.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"Gwhite.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 2)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GWRookB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GWRookW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 4)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GWKnightB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GWKnightW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 6)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GWBishopB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GWBishopW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 7)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GWQueenB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GWQueenW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 8)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GWKingB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GWKingW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 16)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GWPawnB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GWPawnW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 18)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GBRookB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GBRookW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 20)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GBKnightB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GBKnightW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 22)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GBBishopB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GBBishopW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 23)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GBQueenB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GBQueenW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 24)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GBKingB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GBKingW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
	if (i < 32)
	{
		if (((*it).x + (*it).y) % 2)
			bmppaint(hwnd, hdc, L"GBPawnB.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		else
			bmppaint(hwnd, hdc, L"GBPawnW.bmp", 20 + (*it).x * 90, 20 + (*it).y * 90, 90, 90);
		return;
	}
}

void board::invert()
{
	if (is_white_turn)
		for (size_t i = 24; i < 32; i++)
			if (dynamic_cast<pawn*>(a[i])->cond == 1)
				dynamic_cast<pawn*>(a[i])->cond = 2;
	if (!is_white_turn)
		for (size_t i = 8; i < 16; i++)
			if (dynamic_cast<pawn*>(a[i])->cond == 1)
				dynamic_cast<pawn*>(a[i])->cond = 2;
	is_white_turn = !is_white_turn;
	for (size_t i = 0; i < 32; i++)
		if (!a[i]->is_remove())
			a[i]->fset(7 - a[i]->x, 7 - a[i]->y);
}

bool board::is_check()
{
	size_t i = is_white_turn * 16;
	size_t c = i + 16;
	for (; i < c; i++)
	{
		if ((a[i]->click(*this)).is_in(*a[39 - c]))
			return true;
	}
	return false;
}

bool board::is_mate()
{
	size_t i = 16 - is_white_turn * 16;
	size_t c = 16 + i;
	if (!click(a[c - 11]->x, a[c - 11]->y).is_empty())
		return false;
	for (; i < c; i++)
		if (!click(a[i]->x, a[i]->y).is_empty())
			return false;
	return true;
}

set<pos,comp> board::click(unsigned char x, unsigned char y)
{
	figure * t = get_figure(x, y);
	if (!t)
		return set<pos,comp>();
	if (t->colour() != is_white_turn)
		return set<pos, comp>();
	set<pos,comp> res(t->click(*this));
	if (res.is_empty())
		return res;
	set<pos, comp>::iterator it = res.begin();
	set<pos, comp>::iterator it1 = it;
	set<pos, comp>::iterator it2 = res.end();
	while (it != it2)
	{
		t->fset(*it);
		if (is_check())
		{
			++it;
			res.del(*(it1));
			it1 = it;
		}
		else
			++it;
	}
	t->fset(x, y);
	return res;
}

figure * board::get_figure(unsigned char x, unsigned char y)
{
	for (size_t i = 0; i < 32; i++)
		if ((a[i]->x == x) && (a[i]->y == y))
			return a[i];
	return nullptr;
}

void board::place()
{
	a[0]->fset(0, 7);
	a[1]->fset(7, 7);
	a[2]->fset(1, 7);
	a[3]->fset(6, 7);
	a[4]->fset(2, 7);
	a[5]->fset(5, 7);
	a[6]->fset(3, 7);
	a[7]->fset(4, 7);
	for (size_t i = 8; i < 16; i++)
	{
		a[i]->fset(i - 8, 6);
	}
	a[16]->fset(0, 0);
	a[17]->fset(7, 0);
	a[18]->fset(1, 0);
	a[19]->fset(6, 0);
	a[20]->fset(2, 0);
	a[21]->fset(5, 0);
	a[22]->fset(3, 0);
	a[23]->fset(4, 0);
	for (size_t i = 24; i < 32; i++)
	{
		a[i]->fset(i - 24, 1);
	}
	is_white_turn = true;
}