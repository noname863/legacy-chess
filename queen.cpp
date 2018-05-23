#include "figures.h"
set<pos, comp> queen::click(board &_board)
{
	set<pos, comp> res;
	unsigned char i = 1;
	unsigned int x = this->x;
	unsigned int y = this->y;
	while ((x - i < 8) && (y - i < 8))
	{
		if (_board.is_figure(x - i, y - i))
		{
			if (_board.get_figure(x - i, y - i)->colour() != colour())
			{
				res.add(pos(x - i, y - i));
				break;
			}
			break;
		}
		res.add(pos(x - i, y - i));
		i++;
	}
	i = 1;
	while ((x - i < 8) && (y + i < 8))
	{
		if (_board.is_figure(x - i, y + i))
		{
			if (_board.get_figure(x - i, y + i)->colour() != colour())
			{
				res.add(pos(x - i, y + i));
				break;
			}
			break;
		}
		res.add(pos(x - i, y + i));
		i++;
	}
	i = 1;
	while ((x + i < 8) && (y - i < 8))
	{
		if (_board.is_figure(x + i, y - i))
		{
			if (_board.get_figure(x + i, y - i)->colour() != colour())
			{
				res.add(pos(x + i, y - i));
				break;
			}
			break;
		}
		res.add(pos(x + i, y - i));
		i++;
	}
	i = 1;
	while ((x + i < 8) && (y + i < 8))
	{
		if (_board.is_figure(x + i, y + i))
		{
			if (_board.get_figure(x + i, y + i)->colour() != colour())
			{
				res.add(pos(x + i, y + i));
				break;
			}
			break;
		}
		res.add(pos(x + i, y + i));
		i++;
	}
	i = 1;
	while (x - i != UINT32_MAX)
	{
		if (_board.is_figure(x - i, y))
		{
			if (colour() != _board.get_figure(x - i, y)->colour())
			{
				res.add(pos(x - i, y));
				break;
			}
			else
				break;
		}
		res.add(pos(x - i, y));
		i++;
	}
	i = 1;
	while (x + i < 8)
	{
		if (_board.is_figure(x + i, y))
		{
			if (colour() != _board.get_figure(x + i, y)->colour())
			{
				res.add(pos(x + i, y));
				break;
			}
			else
				break;
		}
		res.add(pos(x + i, y));
		i++;
	}
	i = 1;
	while (y - i != UINT32_MAX)
	{
		if (_board.is_figure(x, y - i))
		{
			if (colour() != _board.get_figure(x, y - i)->colour())
			{
				res.add(pos(x, y - i));
				break;
			}
			else
				break;
		}
		res.add(pos(x, y - i));
		i++;
	}
	i = 1;
	while (y + i < 8)
	{
		if (_board.is_figure(x, y + i))
		{
			if (colour() != _board.get_figure(x, y + i)->colour())
			{
				res.add(pos(x, y + i));
				break;
			}
			else
				break;
		}
		res.add(pos(x, y + i));
		i++;
	}
	return res;
}