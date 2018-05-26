#pragma once
#include "windows.h"
#include "set.h"
class pos
{
protected:
	unsigned char x;
	unsigned char y;
public:
	pos() {}
	friend bool comp(const pos &a, const pos &b)
	{
		if (a.x != b.x)
			return a.x > b.x;
		else
			return a.y > b.y;
	}
	friend class board;
	bool operator==(const pos a) { return ((x == a.x) && (y == a.y)); }
	pos(unsigned char x, unsigned char y) { this->x = x; this->y = y; }
	void fset(unsigned char x, unsigned char y) { this->x = x; this->y = y; }
	void fset(const pos a) { x = a.x; y = a.y; }
};

static char count = 0;

class figure : public pos
{
protected:
	unsigned char id;
public:
	figure() { id = count; count++; }
	~figure() { count--; }
	bool colour() { return id < 16; }
	void remove() { x = y = 255; }
	bool is_remove() { return ((x == 255) && (y == 255)); }
	virtual set<pos, comp> click(board &) { return set<pos, comp>(); }
};


class board
{
private:
	figure ** a;
public:
	bool is_white_turn;
	board();
	~board();
	bool is_figure(unsigned char, unsigned char);
	void draw(HDC, HWND);
	void to_colour(HDC, HWND, set<pos, comp> &);
	void invert();
	bool is_check();
	bool is_mate();
	void place();
	set<pos,comp> click(unsigned char, unsigned char);
	figure * get_figure(unsigned char, unsigned char); //с указателем можно спокойно возвращать null
};

#ifndef _BOARD
#define _BOARD
//static board _board;
#endif

class rook : public figure
{
public:
	set<pos, comp> click(board &);
};


class bishop : public figure
{
public:
	set<pos, comp> click(board &);
};


class queen : public figure
{
public:
	set<pos, comp> click(board &);
};


class knight : public figure
{
public:
	set<pos, comp> click(board &);
};


class pawn : public figure
{
public:
	pawn() : figure() { cond = 0; }
	unsigned char cond;
	set<pos, comp> click(board &);
};


class king : public figure
{
public:
	set<pos, comp> click(board &);
};
