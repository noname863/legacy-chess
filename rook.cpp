#pragma once
#include "figures.h"
set<pos, comp> rook::click()
{
	set<pos, comp> res;
	unsigned char i = 1;
	unsigned char j = 0;
	while (x - i != 255)
	{
		if (_board.is_figure(x - i, y))
		{
			if (colour() != _board.get_figure(x - i, y)->colour())
			{
				res.add(pos(x - i, y));
				j++;
				break;
			}
			else
				break;
		}
		res.add(pos(x - i, y));
		j++;
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
				j++;
				break;
			}
			else
				break;
		}
		res.add(pos(x - i, y));
		j++;
		i++;
	}
	i = 1;
	while (y - i != 255)
	{
		if (_board.is_figure(x, y - i))
		{
			if (colour() != _board.get_figure(x, y - i)->colour())
			{
				res.add(pos(x, y - i));
				j++;
				break;
			}
			else
				break;
		}
		res.add(pos(x, y - i));
		j++;
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
				j++;
				break;
			}
			else
				break;
		}
		res.add(pos(x, y - i));
		j++;
		i++;
	}
	return res;
}