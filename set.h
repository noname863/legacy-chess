#pragma once//#include <algorithm>
#include "stack.h"
#define NULL 0
//red-black tree
template <class T,bool comp(const T &, const T &)>
class set  
{
private:
	struct node
	{
		node * left;
		node * right;
		bool is_red;
		T value;

		node();
		node(const node &);
		node(const T &);
		~node();

		node & operatop=(const node &);

		node * rotateleft();
		node * rotateright();
	};

	node * root;

public:
	set();
	set(const T &);
	set(const T *, size_t);
	set(const set<T, comp> &);
	~set();
	bool is_empty();
	bool add(const T &); //true если добавлен. false если элемент уже есть
	bool del(const T &); //true если удален. false если такого нет
	bool is_in(const T &);
	friend set<T, comp> operator|(const set<T, comp> &, const set<T, comp> &);  //Объединение множеств
	friend set<T, comp> operator/(const set<T, comp> &, const set<T, comp> &);  //Разность множеств
	friend set<T, comp> operator^(const set<T, comp> &, const set<T, comp> &);  //Симметрическая разность множества
	friend set<T, comp> operator&(const set<T, comp> &, const set<T, comp> &);  //Пересечение множеств
	set<T, comp> & operator|=(const set<T, comp> &);
	set<T, comp> & operator/=(const set<T, comp> &);
	set<T, comp> & operator^=(const set<T, comp> &);
	set<T, comp> & operator&=(const set<T, comp> &);
};


template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::node()
{
	is_red = false;
	left = NULL;
	right = NULL;
}


template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::node(const node &b)
{
	is_red = b.is_red;
	value = b.value;
	left = new node(*b.left);
	right = new node(*b.right);
}


template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::node(const T &val)
{
	value = val;
	is_red = false;
	left = NULL;
	right = NULL;
}


template <class T, bool comp(const T &, const T &)>
set<T, comp>::node::~node()
{
	if (left != NULL)
		delete left;
	if (left != NULL)
		delete right;
}


template <class T, bool comp(const T &, const T &)>
node * set<T, comp>::node::rotateleft()
{
	node * b = right;
	right = b.left;
	b.left = *this;
	return b;
}


template <class T, bool comp(const T &, const T &)>
node * set<T, comp>::node::rotateright()
{
	node * b = left;
	left = b.right;
	b.right = *this;
	return b;
}


template <class T, bool comp(const T &, const T &)>
set<T, comp>::set()
{
	root = NULL;
}


template <class T, bool comp(const T &, const T &)>
set<T, comp>::set(const T &b)
{
	root = new node;
	root->value = b;
}


template <class T, bool comp(const T &, const T &)>
set<T, comp>::set(const set<T, comb> &b)
{
	root = new node(*b.root);
}


template <class T, bool comp(const T &, const T &)>
set<T, comp>::~set()
{
	delete root;
}


template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::is_empty()
{
	return root == NULL;
}


template <class T, bool comp(const T &, const T &)>
bool set<T, comp>::add(const T &b)
{
	stack<node*> path;
	node * it = root;
	while (it)
	{
		if (it->value == b)
			return false;
		path.push(it);
		if (comp(it->value, b))
			it = it->right;
		else
			it = it->left;
	}
	it = new node(b);
	it->is_red = true;
	it = path.top();
	path.pop();
	node * st2;
	if (it->is_red)
	{
		it = path.top();
		path.pop();
		if (it->right->is_red && it->left->is_red)
		{
			while (it->is_red)
			{
				it->is_red = true;
				it->right->is_red = false;
				it->left->is_red = false;
				if (path.is_empty())
				{
					it->is_red = false;
					return true;
				}
				st2 = path.top();
				path.pop();
				if (path.is_empty())//если дошел до вершины то закончить
				{
					st2->is_red = false;
					return true;
				}
				if (!st2->is_red)//если st2 черный то закончить
					return true;
				//поиск направления не st2 и проверка
				it = path.top();
				path.pop();
				if ((it->left == st2) && (!it->left->is_red))
				{
					st2->is_red = false;
					return true;
				}
				if ((it->right == st2) && (!it->right->is_red))
				{
					st2->is_red = false;
					return true;
				}
			}
			return true;
		}
		node * it2 = path.top();
		if (it->right->is_red)
		{
			it->right->is_red = false;
			it->left->is_red = true;
			if (it->right->right->value == b)
			{
				if (it2->right = it)
					it2->right = it.rotateleft();
				else
					it2->left = it.rotateleft();
			}
			else
			{
				it->right = it->right.rotateright();
				if (it2->right = it)
				{
					it2->right = it.rotateleft();
				}
				else
					it2->left = it.rotateleft();
			}
		}
		else
		{
			it->right->is_red = true;
			it->left->is_red = false;
			if (it->left->right->value == b)
			{
				if (it2->right = it)
					it2->right = it.rotateright();
				else
					it2->left = it.rotateright();
			}
			else
			{
				it->left = it->left.rotateleft();
				if (it2->right = it)
				{
					it2->right = it.rotateright();
				}
				else
					it2->left = it.rotateright();
			}
		}
	}
	return true;
}