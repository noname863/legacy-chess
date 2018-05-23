#include "figures.h"
set<pos, comp> knight::click(board &_board)
{
	pos * res = new pos[8];
	unsigned char j = 0;
	unsigned int x = this->x;
	unsigned int y = this->y;
	if ((x - 2 < 8) && (y - 1 < 8))
	{
		res[j] = pos(x - 2, y - 1);
		j++;
	}
	if (_board.is_figure(x - 2, y - 1))
		if (_board.get_figure(x - 2, y - 1)->colour() == colour())
			j--;

	if ((x - 1 < 8) && (y - 2 < 8))
	{
		res[j] = pos(x - 1, y - 2);
		j++;
	}
	if (_board.is_figure(x - 1, y - 2))
		if (_board.get_figure(x - 1, y - 2)->colour() == colour())
			j--;

	if ((x + 2 < 8) && (y + 1 < 8))
	{
		res[j] = pos(x + 2, y + 1);
		j++;
	}
	if (_board.is_figure(x + 2, y + 1))
		if (_board.get_figure(x + 2, y + 1)->colour() == colour())
			j--;

	if ((x + 1 < 8) && (y + 2 < 8))
	{
		res[j] = pos(x + 1, y + 2);
		j++;
	}
	if (_board.is_figure(x + 1, y + 2))
		if (_board.get_figure(x + 1, y + 2)->colour() == colour())
			j--;

	if ((x + 2 < 8) && (y - 1 < 8))
	{
		res[j] = pos(x + 2, y - 1);
		j++;
	}
	if (_board.is_figure(x + 2, y - 1))
		if (_board.get_figure(x + 2, y - 1)->colour() == colour())
			j--;

	if ((x + 1 < 8) && (y - 2 < 8))
	{
		res[j] = pos(x + 1, y - 2);
		j++;
	}
	if (_board.is_figure(x + 1, y - 2))
		if (_board.get_figure(x + 1, y - 2)->colour() == colour())
			j--;

	if ((x - 2 < 8) && (y + 1 < 8))
	{
		res[j] = pos(x - 2, y + 1);
		j++;
	}
	if (_board.is_figure(x - 2, y + 1))
		if (_board.get_figure(x - 2, y + 1)->colour() == colour())
			j--;

	if ((x - 1 < 8) && (y + 2 < 8))
	{
		res[j] = pos(x - 1, y + 2);
		j++;
	}
	if (_board.is_figure(x - 1, y + 2))
		if (_board.get_figure(x - 1, y + 2)->colour() == colour())
			j--;

	set<pos, comp> a;
	for (unsigned char i = 0; i < j; i++)
		a.add(res[i]);
	delete[] res;
	return a;
}
