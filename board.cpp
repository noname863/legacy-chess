#pragma once
#include "figures.h"
board::board()
{
	a = new figure*[32];
	a[0] = new rook;
	a[1] = new rook;
	a[2] = new knight;
	a[3] = new knight;
	a[4] = new bishop;
	a[5] = new bishop;
	a[6] = new queen;
	a[7] = new king;
	a[8] = new pawn;
	a[9] = new pawn;
	a[10] = new pawn;
	a[11] = new pawn;
	a[12] = new pawn;
	a[13] = new pawn;
	a[14] = new pawn;
	a[15] = new pawn;
	a[16] = new rook;
	a[17] = new rook;
	a[18] = new knight;
	a[19] = new knight;
	a[20] = new bishop;
	a[21] = new bishop;
	a[22] = new queen;
	a[23] = new king;
	a[24] = new pawn;
	a[25] = new pawn;
	a[26] = new pawn;
	a[27] = new pawn;
	a[28] = new pawn;
	a[29] = new pawn;
	a[30] = new pawn;
	a[31] = new pawn;
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


figure * board::get_figure(unsigned char x, unsigned char y)
{
	for (size_t i = 0; i < 32; i++)
		if ((a[i]->x == x) && (a[i]->y == y))
			return a[i];
	return nullptr;
}
