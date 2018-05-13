#pragma once
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
	pos(unsigned char x, unsigned char y) { this->x = x; this->y = y; }
	void fset(unsigned char x, unsigned char y) { this->x = x; this->y = y; }
};


static char count = 0;
class figure : public pos
{
protected:
	unsigned char id;
public:
	friend class board;
	figure() { id = count; count++; }
	~figure() { count--; }
	bool colour() { return id < 16; }
	void remove() { x = y = 255; }
	bool is_remove() { return ((x == 255) && (y == 255)); }
	virtual set<pos, comp> click() { return set<pos, comp>(); }
};



class board
{
private:
	figure ** a;
public:
	board();
	~board();
	bool is_figure(unsigned char, unsigned char);
	figure * get_figure(unsigned char, unsigned char); //с указателем можно спокойно возвращать null
};

static board _board;

class rook : public figure
{
public:
	set<pos, comp> click();
};


class bishop : public figure
{
public:
	set<pos, comp> click();
};


class queen : public figure
{
public:
	set<pos, comp> click();
};


class knight : public figure
{
public:
	set<pos, comp> click();
};


class pawn : public figure
{
public:
	set<pos, comp> click() { return set<pos, comp>(); }
};


class king : public figure
{
public:
	set<pos, comp> click() { return set<pos, comp>(); }
};