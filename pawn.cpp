#include "figures.h"
#include "set.h"
set<pos, comp> pawn::click(board &_board)
{
	if (is_remove())
		return set<pos, comp>();
	set<pos, comp> res;
	if (!_board.is_figure(x, y - 1))
	{
		if ((cond == 0) && (!_board.is_figure(x, y - 2)))
			res.add(pos(x, y - 2));
		res.add(pos(x, y - 1));
	}
	if ((_board.is_figure(x + 1, y - 1)) && (_board.get_figure(x + 1, y - 1)->colour() != colour()))
		res.add(pos(x + 1, y - 1));
	if ((_board.is_figure(x - 1, y - 1)) && (_board.get_figure(x - 1, y - 1)->colour() != colour()))
		res.add(pos(x - 1, y - 1));
	pawn * t;
	if (t = dynamic_cast<pawn*> (_board.get_figure(x - 1, y)))
		if ((t->cond == 1) && (t->colour() != colour()))
			res.add(pos(x - 1, y - 1));
	if (t = dynamic_cast<pawn*> (_board.get_figure(x + 1, y)))
		if ((t->cond == 1) && (t->colour() != colour()))
			res.add(pos(x + 1, y - 1));
	return res;
}