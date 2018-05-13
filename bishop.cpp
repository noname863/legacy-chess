#include "figures.h"
set<pos, comp> bishop::click()
{
	set<pos, comp> res;
	unsigned char i = 1;
	unsigned char j = 0;
	while ((x - i < 8) && (y - i < 8))
	{
		if (_board.is_figure(x - i, y - i))
		{
			if (_board.get_figure(x - i, y - i)->colour() != colour())
			{
				res.add(pos(x - i, y - i));
				break;
			}
		}
		res.add(pos(x - i, y - i));
		i++;
		j++;
	}
	i = 0;
	while ((x - i < 8) && (y + i < 8))
	{
		if (_board.is_figure(x - i, y + i))
		{
			if (_board.get_figure(x - i, y + i)->colour() != colour())
			{
				res.add(pos(x - i, y + i));
				break;
			}
		}
		res.add(pos(x - i, y + i));
		i++;
		j++;
	}
	i = 0;
	while ((x + i < 8) && (y - i < 8))
	{
		if (_board.is_figure(x + i, y - i))
		{
			if (_board.get_figure(x + i, y - i)->colour() != colour())
			{
				res.add(pos(x + i, y - i));
				break;
			}
		}
		res.add(pos(x + i, y - i));
		i++;
		j++;
	}
	i = 0;
	while ((x + i < 8) && (y + i < 8))
	{
		if (_board.is_figure(x + i, y + i))
		{
			if (_board.get_figure(x + i, y + i)->colour() != colour())
			{
				res.add(pos(x + i, y + i));
				break;
			}
		}
		res.add(pos(x + i, y + i));
		i++;
		j++;
	}
	return res;
}
//(8-6)*(9+(6-3))