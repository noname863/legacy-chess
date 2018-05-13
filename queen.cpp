#include "figures.h"
set<pos, comp> queen::click()
{
	set<pos, comp> res;
	rook a;
	a.fset(x, y);
	bishop b;
	b.fset(x, y);
	res = a.click() | b.click();
	return res;
}