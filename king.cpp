#include "figures.h"

set<pos, comp> king::click(board &_board)
{
	set<pos, comp> res;
	if (y - 1 >= 0)
		if (_board.is_figure(x, y - 1))
		{
			if (_board.get_figure(x, y - 1)->colour() != colour())
			{
				res.add(pos(x, y - 1));
			}
		}
		else
			res.add(pos(x, y - 1));
	if ((y - 1 >= 0) && (x + 1 < 8))
		if (_board.is_figure(x + 1, y - 1))
		{
			if (_board.get_figure(x + 1, y - 1)->colour() != colour())
			{
				res.add(pos(x + 1, y - 1));
			}
		}
		else
			res.add(pos(x + 1, y - 1));
	if (x + 1 < 8)
		if (_board.is_figure(x + 1, y))
		{
			if (_board.get_figure(x + 1, y)->colour() != colour())
			{
				res.add(pos(x + 1, y));
			}
		}
		else
			res.add(pos(x + 1, y));
	if ((x + 1 < 8) && (y + 1 < 8))
		if (_board.is_figure(x + 1, y + 1))
		{
			if (_board.get_figure(x + 1, y + 1)->colour() != colour())
			{
				res.add(pos(x + 1, y + 1));
			}
		}
		else
			res.add(pos(x + 1, y + 1));
	if (y + 1 < 8)
		if (_board.is_figure(x, y + 1))
		{
			if (_board.get_figure(x, y + 1)->colour() != colour())
			{
				res.add(pos(x, y + 1));
			}
		}
		else
			res.add(pos(x, y + 1));
	if ((y + 1 < 8) && (x - 1 >= 0))
		if (_board.is_figure(x - 1, y + 1))
		{
			if (_board.get_figure(x - 1, y + 1)->colour() != colour())
			{
				res.add(pos(x - 1, y + 1));
			}
		}
		else
			res.add(pos(x - 1, y + 1));
	if (x - 1 >= 0)
		if (_board.is_figure(x - 1, y))
		{
			if (_board.get_figure(x - 1, y)->colour() != colour())
			{
				res.add(pos(x - 1, y));
			}
		}
		else
			res.add(pos(x - 1, y));
	if ((x - 1 >= 0) && (y - 1 >= 0))
		if (_board.is_figure(x - 1, y - 1))
		{
			if (_board.get_figure(x - 1, y - 1)->colour() != colour())
			{
				res.add(pos(x - 1, y - 1));
			}
		}
		else
			res.add(pos(x - 1, y - 1));
	if ((!is_moved) && (!_board.is_figure(x + 1, y)))
	{
		fset(x + 1, y);
		is_moved = true;
		if ((!_board.is_check()) && (!_board.is_figure(x + 1, y)) && (dynamic_cast<rook*>(_board.get_figure(7, 7))) && (!dynamic_cast<rook*>(_board.get_figure(7, 7))->is_moved) && (!_board.is_figure(6, 7)))
			res.add(pos(x + 1, y));
		fset(x - 1, y);
		is_moved = false;
	}
	if ((!is_moved) && (!_board.is_figure(x - 1, y)))
	{
		fset(x - 1, y);
		is_moved = true;
		if ((!_board.is_check()) && (!_board.is_figure(x - 2, y)) && (dynamic_cast<rook*>(_board.get_figure(0, 7))) && (!dynamic_cast<rook*>(_board.get_figure(0, 7))->is_moved) && (!_board.is_figure(1, 7)))
			res.add(pos(x - 2, y));
		fset(x + 1, y);
		is_moved = false;
	}
	return res;
}
